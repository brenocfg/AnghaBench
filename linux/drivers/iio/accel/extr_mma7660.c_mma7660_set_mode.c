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
struct mma7660_data {int mode; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum mma7660_mode { ____Placeholder_mma7660_mode } mma7660_mode ;

/* Variables and functions */
 int MMA7660_MODE_ACTIVE ; 
 int /*<<< orphan*/  MMA7660_REG_MODE ; 
 int MMA7660_REG_MODE_BIT_MODE ; 
 int MMA7660_REG_MODE_BIT_TON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma7660_set_mode(struct mma7660_data *data,
				enum mma7660_mode mode)
{
	int ret;
	struct i2c_client *client = data->client;

	if (mode == data->mode)
		return 0;

	ret = i2c_smbus_read_byte_data(client, MMA7660_REG_MODE);
	if (ret < 0) {
		dev_err(&client->dev, "failed to read sensor mode\n");
		return ret;
	}

	if (mode == MMA7660_MODE_ACTIVE) {
		ret &= ~MMA7660_REG_MODE_BIT_TON;
		ret |= MMA7660_REG_MODE_BIT_MODE;
	} else {
		ret &= ~MMA7660_REG_MODE_BIT_TON;
		ret &= ~MMA7660_REG_MODE_BIT_MODE;
	}

	ret = i2c_smbus_write_byte_data(client, MMA7660_REG_MODE, ret);
	if (ret < 0) {
		dev_err(&client->dev, "failed to change sensor mode\n");
		return ret;
	}

	data->mode = mode;

	return ret;
}