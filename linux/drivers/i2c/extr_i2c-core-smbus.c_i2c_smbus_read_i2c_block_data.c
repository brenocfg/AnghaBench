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
union i2c_smbus_data {int* block; } ;
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  I2C_SMBUS_I2C_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 

s32 i2c_smbus_read_i2c_block_data(const struct i2c_client *client, u8 command,
				  u8 length, u8 *values)
{
	union i2c_smbus_data data;
	int status;

	if (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;
	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, command,
				I2C_SMBUS_I2C_BLOCK_DATA, &data);
	if (status < 0)
		return status;

	memcpy(values, &data.block[1], data.block[0]);
	return data.block[0];
}