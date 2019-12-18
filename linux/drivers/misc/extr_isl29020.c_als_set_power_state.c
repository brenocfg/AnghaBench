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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static void als_set_power_state(struct i2c_client *client, int enable)
{
	int ret_val;

	ret_val = i2c_smbus_read_byte_data(client, 0x00);
	if (ret_val < 0)
		return;

	if (enable)
		ret_val |= 0x80;
	else
		ret_val &= 0x7F;

	i2c_smbus_write_byte_data(client, 0x00, ret_val);
}