/*Created  by Raj Singha on 15/12/2019*/

/*
 * MIT License

Copyright (c) 2019 Raj Singha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

 
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "your_firebase_database_link" // Add your firebase databse link
#define FIREBASE_AUTH "your_databse_key" // Add your database  key
#define WIFI_SSID "your_wifi_name" // your wifi ssid
#define WIFI_PASS "your_wifi_pass" // your wifi password

#define DHTPIN 0 

DHT dht(DHTPIN, DHT11);



HTTPClient http;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  dht.begin();

  Serial.println("Connecting to ");
       Serial.println(WIFI_SSID); 
 
       WiFi.begin(WIFI_SSID,WIFI_PASS); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

 

  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);

  Firebase.set("SensorData/0/area","Kalyani,Nadia"); //Json Object in databse


  
  
}








void loop(){


   float h = dht.readHumidity();
   float t = dht.readTemperature();

   Firebase.set("SensorData/0/temp",t);
   Firebase.set("SensorData/0/humidity",h);

   delay(2000);
   

}

 
