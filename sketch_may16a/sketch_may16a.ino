#include <Wire.h>

int address1 = 0x27;  //decimal address of sensor 1
unsigned long reading = 0;
float output = 0;
 
void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire object

  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
}
 
void loop() {
  read_hum(address1);  
}
 
int read_hum(int address) {
Wire.beginTransmission(address); // transmit to device #66
Wire.write(byte(255));      // sets register pointer to echo #1 register
Wire.endTransmission();      // stop transmitting

 // step 4: request reading from sensor
 Wire.requestFrom(address, 2);    // request 2 bytes from slave device #112

 // step 5: receive reading from sensor
 if(2 <= Wire.available())    // if two bytes were received
 {
   reading = Wire.read();  // receive high byte (overwrites previous reading)
   reading = reading << 6;    // shift high byte to be high 8 bits
   reading |= Wire.read(); // receive low byte as lower 8 bits
   output = reading;
   output = output*200/16382;
   Serial.print(output);   // print the reading
   Serial.println(",");
 }

   delay(1000); 
}
