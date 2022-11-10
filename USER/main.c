#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "dht11.h"
#include "pcf8574.h"

/************************************************
 ALIENTEK ������STM32F429������ʵ��33
 DHT11������ʪ�ȴ�����ʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

int main(void)
{
	u8 t=0;			     
	u8 temperature;  	    
	u8 humidity;    
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART	
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //��ʼ��SDRAM
    LCD_Init();                     //��ʼ��LCD
    PCF8574_Init();                 //��ʼ��PCF8574
   	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Apollo STM32F4/F7"); 
	LCD_ShowString(30,70,200,16,16,"DHT11 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2016/1/16");	
    PCF8574_ReadBit(BEEP_IO);       //����DHT11��PCF8574���ж����Ź���һ��IO��
                                    //�����ڳ�ʼ��DHT11֮ǰҪ�ȶ�ȡһ��PCF8574������һ��IO��
                                    //ʹ���ͷŵ��ж�������ռ�õ�IO(PB12����),�����ʼ��DS18B20�������    
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(30,130,200,16,16,"DHT11 OK");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(30,150,200,16,16,"Temp:  C");	 
 	LCD_ShowString(30,170,200,16,16,"Humi:  %");
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{	
            PCF8574_ReadBit(BEEP_IO);   //��ȡһ��PCF8574������һ��IO��ʹ���ͷŵ�PB12���ţ�
                                        //�����ȡDHT11���ܻ������            
			DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ					    
			LCD_ShowNum(30+40,150,temperature,2,16);		//��ʾ�¶�	   		   
			LCD_ShowNum(30+40,170,humidity,2,16);			//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}						    
}
