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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int flags; } ;

/* Variables and functions */
 int I2C_CLIENT_PEC ; 
 int adm1032_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm90_read_reg(struct i2c_client *client, u8 reg)
{
	int err;

	if (client->flags & I2C_CLIENT_PEC) {
		err = adm1032_write_byte(client, reg);
		if (err >= 0)
			err = i2c_smbus_read_byte(client);
	} else
		err = i2c_smbus_read_byte_data(client, reg);

	return err;
}