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
 int ADG792A_LDSW ; 
 int ADG792A_RESETB ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int adg792a_write_cmd(struct i2c_client *i2c, u8 cmd, int reset)
{
	u8 data = ADG792A_RESETB | ADG792A_LDSW;

	/* ADG792A_RESETB is active low, the chip resets when it is zero. */
	if (reset)
		data &= ~ADG792A_RESETB;

	return i2c_smbus_write_byte_data(i2c, cmd, data);
}