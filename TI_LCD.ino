#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define sensor 0x40
LiquidCrystal_I2C lcd(0x20,16,2);
void setup() {
  Wire.begin();
  Serial.begin(9600);  
  delay(300);
  lcd.init();                     
  lcd.backlight();
  lcd.print("TI 154 Test");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");}

void loop() {
unsigned int data[2];  
Wire.beginTransmission(sensor);  

Wire.write(0xF5);  
Wire.endTransmission();  

delay(500);

// Request 2 bytes of data  

Wire.requestFrom(sensor, 2);

// Read 2 bytes of data  

// humidity msb, humidity lsb  

if(Wire.available() == 2)  

{    

data[0] = Wire.read();    

data[1] = Wire.read();

// Convert the data    

float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;

// Output data to Serial Monitor    

Serial.print("Relative Humidity :");    

Serial.print(humidity);    

Serial.println(" %RH");  

}

// Start I2C transmission  

Wire.beginTransmission(sensor);  

// Send temperature measurement command, NO HOLD master  

Wire.write(0xF3);  

// Stop I2C transmission  

Wire.endTransmission();  

delay(500);

// Request 2 bytes of data  

Wire.requestFrom(sensor, 2);

// Read 2 bytes of data  

// temp msb, temp lsb  

if(Wire.available() == 2)  

{    

data[0] = Wire.read();    

data[1] = Wire.read();

// Convert the data    

float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;    


// Output data to Serial Monitor    

Serial.print("Temperature in Celsius :");    

Serial.print(cTemp);    Serial.println(" C");    

delay(300);
lcd.setCursor(0, 1);
lcd.print(cTemp);

}  

}

