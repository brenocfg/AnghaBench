#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct corgi_lcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcdtg_i2c_send_byte (struct corgi_lcd*,int,int) ; 
 int /*<<< orphan*/  lcdtg_i2c_send_start (struct corgi_lcd*,int) ; 
 int /*<<< orphan*/  lcdtg_i2c_send_stop (struct corgi_lcd*,int) ; 
 int /*<<< orphan*/  lcdtg_i2c_wait_ack (struct corgi_lcd*,int) ; 

__attribute__((used)) static void lcdtg_set_common_voltage(struct corgi_lcd *lcd,
				     uint8_t base_data, uint8_t data)
{
	/* Set Common Voltage to M62332FP via I2C */
	lcdtg_i2c_send_start(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, 0x9c);
	lcdtg_i2c_wait_ack(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, 0x00);
	lcdtg_i2c_wait_ack(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, data);
	lcdtg_i2c_wait_ack(lcd, base_data);
	lcdtg_i2c_send_stop(lcd, base_data);
}