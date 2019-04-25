#include <ESP8266WiFi.h>
#include <WiFiClient.h>


#ifndef APSSID
#define APSSID "PaulESP"
#define APPSK  "paulsin91@"
#endif

// Variable to store the HTTP request
String header;

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

int ledPin = 13; // GPIO13
WiFiServer server(80);

const char* value = "";

// Auxiliar variables to store the current output state
String output4State = "off";
String output12State = "off";
String output13State = "off";
String output14State = "off";
String output16State = "off";

// Assign output variables to GPIO pins
const int output4 = 4;
const int output12 = 12;
const int output13 = 13;
const int output14 = 14;
const int output16 = 16;

void setup() {

   Serial.begin(115200);
   delay(10);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH); // turn on

  // Initialize the output variables as outputs
  pinMode(output16, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output13, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output4, OUTPUT);
  
  // Set outputs to LOW

  digitalWrite(output16, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output13, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output4, LOW);

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password);
   IPAddress myIP = WiFi.softAPIP();
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("New Client");
    String currentLine = "";
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if(c == '\n') {
          if(currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println(); 


            // turns the GPIOs on and off
            if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 5 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 5 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
            }
         
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 10px 30px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Display current state, and ON/OFF buttons for GPIO 16  
            client.println("<p>GPIO 16 - State " + output16State + "</p>");
            // If the output16State is off, it displays the ON button       
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p>GPIO 14 - State " + output14State + "</p>");
            // If the output14State is off, it displays the ON button       
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 13 - State " + output13State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            // Display current state, and ON/OFF buttons for GPIO 12  
            client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // If the output12State is off, it displays the ON button       
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c!='\r') {
            currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client Disconnected");
    Serial.println("");
  }
}
