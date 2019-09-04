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
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  adapter; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_WRITE ; 
 int i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 adv_smbus_write_byte_data(struct i2c_client *client,
				     u8 command, u8 value)
{
	union i2c_smbus_data data;
	int err;
	int i;

	data.byte = value;
	for (i = 0; i < 3; i++) {
		err = i2c_smbus_xfer(client->adapter, client->addr,
				     client->flags,
				     I2C_SMBUS_WRITE, command,
				     I2C_SMBUS_BYTE_DATA, &data);
		if (!err)
			break;
	}
	if (err < 0)
		v4l_err(client, "error writing %02x, %02x, %02x\n",
			client->addr, command, value);
	return err;
}