#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,A1,A2,A3,A4);
int red = 9;
int blue =10;
int green =11;
int buzzer = 8;
float tempcelsius;
int sensor = A0;
int servo = 6;
int motor = 5;
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(motor,OUTPUT);
  pinMode(servo,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  
}
 
void loop(){

  
  tempcelsius = analogRead(sensor)*0.004882814; // 5/1024 //we will need to first find the percentage of 5V on the input
  	tempcelsius = (tempcelsius - 0.5) * 100.0; //converting it to degrees c, minusing to get the range between 0.5 -1.25
  
  if(tempcelsius>=17.0){
    lcd.setCursor(0,0);
	lcd.print("Temp: ");
  	lcd.print(tempcelsius);
    lcd.setCursor(1,1);
    lcd.print("Danger high temp");
    Serial.println("HIGH temp");
    delay(2000);
    digitalWrite(red,HIGH);
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    tone(buzzer,1000);
    delay(1000);
  }
  
  
else if(tempcelsius >= 13.0 && tempcelsius <=16.9)
  {
    lcd.setCursor(0,0);
	lcd.print("Temp: ");
  	lcd.print(tempcelsius);
    lcd.setCursor(1,1);
    lcd.print("Acceptable temp");
    Serial.println("Acceptable");
  delay(2000);
    digitalWrite(red,HIGH);
    digitalWrite(blue,LOW);
    digitalWrite(green,HIGH);
  	noTone(buzzer);
  }
  else if(tempcelsius <=2.0){
    
    lcd.setCursor(0,0);
	lcd.print("Temp: ");
  	lcd.print(tempcelsius);
    lcd.setCursor(1,1);
    lcd.print("TOO LOW");
    Serial.println("TOO LOW");
    delay(2000);
    digitalWrite(red,LOW);
    digitalWrite(blue,HIGH);
    digitalWrite(green,LOW);
    noTone(buzzer);
  }
  
/*btooth mod , to view temp levels */ 
   
  if(Serial.available()){ //check what is avail in serial monitor
    String data = Serial.readString();
    Serial.print("data=");
    Serial.println(data);
    Serial.println();
  
  if (data== "view temperature"|| data=="stop" || data=="temp"){
    Serial.println("tempcelsius=");
    Serial.println(tempcelsius);
    noTone(buzzer);
    delay(1000);
  }
   else if (data== "cool"){
    //int B = map(sensor,0,1023,0,255);
    
  	analogWrite(servo,180);
    analogWrite(motor,255);
    Serial.println("cooling system initiated"); 
  }
  
  else if(data=="heat"){
    analogWrite(servo,1);
    //delay?
    analogWrite(motor,LOW);
    Serial.println(" cooling system turned off");
    
  }
    
  
 }
  
  
  
}
