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
union i2c_smbus_data {unsigned int* block; } ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 unsigned int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  I2C_SMBUS_I2C_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 

__attribute__((used)) static int adv_smbus_read_i2c_block_data(struct i2c_client *client,
					 u8 command, unsigned length, u8 *values)
{
	union i2c_smbus_data data;
	int ret;

	if (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;

	ret = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			     I2C_SMBUS_READ, command,
			     I2C_SMBUS_I2C_BLOCK_DATA, &data);
	memcpy(values, data.block + 1, length);
	return ret;
}