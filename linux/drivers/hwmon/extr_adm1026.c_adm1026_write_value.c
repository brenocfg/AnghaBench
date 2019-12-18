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
typedef  int u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int adm1026_write_value(struct i2c_client *client, u8 reg, int value)
{
	int res;

	if (reg < 0x80) {
		/* "RAM" locations */
		res = i2c_smbus_write_byte_data(client, reg, value);
	} else {
		/* EEPROM, do nothing */
		res = 0;
	}
	return res;
}