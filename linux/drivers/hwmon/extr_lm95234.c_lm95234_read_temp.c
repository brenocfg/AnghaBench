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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  LM95234_REG_TEMPH (int) ; 
 int /*<<< orphan*/  LM95234_REG_TEMPL (int) ; 
 int /*<<< orphan*/  LM95234_REG_UTEMPH (int) ; 
 int /*<<< orphan*/  LM95234_REG_UTEMPL (int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm95234_read_temp(struct i2c_client *client, int index, int *t)
{
	int val;
	u16 temp = 0;

	if (index) {
		val = i2c_smbus_read_byte_data(client,
					       LM95234_REG_UTEMPH(index - 1));
		if (val < 0)
			return val;
		temp = val << 8;
		val = i2c_smbus_read_byte_data(client,
					       LM95234_REG_UTEMPL(index - 1));
		if (val < 0)
			return val;
		temp |= val;
		*t = temp;
	}
	/*
	 * Read signed temperature if unsigned temperature is 0,
	 * or if this is the local sensor.
	 */
	if (!temp) {
		val = i2c_smbus_read_byte_data(client,
					       LM95234_REG_TEMPH(index));
		if (val < 0)
			return val;
		temp = val << 8;
		val = i2c_smbus_read_byte_data(client,
					       LM95234_REG_TEMPL(index));
		if (val < 0)
			return val;
		temp |= val;
		*t = (s16)temp;
	}
	return 0;
}