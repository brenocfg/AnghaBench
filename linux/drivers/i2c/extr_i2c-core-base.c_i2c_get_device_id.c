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
struct i2c_device_identity {int manufacturer_id; int part_id; int die_revision; } ;
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_ADDR_DEVICE_ID ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int /*<<< orphan*/  I2C_SMBUS_I2C_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_xfer (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 

int i2c_get_device_id(const struct i2c_client *client,
		      struct i2c_device_identity *id)
{
	struct i2c_adapter *adap = client->adapter;
	union i2c_smbus_data raw_id;
	int ret;

	if (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		return -EOPNOTSUPP;

	raw_id.block[0] = 3;
	ret = i2c_smbus_xfer(adap, I2C_ADDR_DEVICE_ID, 0,
			     I2C_SMBUS_READ, client->addr << 1,
			     I2C_SMBUS_I2C_BLOCK_DATA, &raw_id);
	if (ret)
		return ret;

	id->manufacturer_id = (raw_id.block[1] << 4) | (raw_id.block[2] >> 4);
	id->part_id = ((raw_id.block[2] & 0xf) << 5) | (raw_id.block[3] >> 3);
	id->die_revision = raw_id.block[3] & 0x7;
	return 0;
}