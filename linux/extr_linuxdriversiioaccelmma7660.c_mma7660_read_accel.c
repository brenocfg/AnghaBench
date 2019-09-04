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
struct mma7660_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MMA7660_I2C_READ_RETRIES ; 
 int MMA7660_REG_OUT_BIT_ALERT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma7660_read_accel(struct mma7660_data *data, u8 address)
{
	int ret, retries = MMA7660_I2C_READ_RETRIES;
	struct i2c_client *client = data->client;

	/*
	 * Read data. If the Alert bit is set, the register was read at
	 * the same time as the device was attempting to update the content.
	 * The solution is to read the register again. Do this only
	 * MMA7660_I2C_READ_RETRIES times to avoid spending too much time
	 * in the kernel.
	 */
	do {
		ret = i2c_smbus_read_byte_data(client, address);
		if (ret < 0) {
			dev_err(&client->dev, "register read failed\n");
			return ret;
		}
	} while (retries-- > 0 && ret & MMA7660_REG_OUT_BIT_ALERT);

	if (ret & MMA7660_REG_OUT_BIT_ALERT) {
		dev_err(&client->dev, "all register read retries failed\n");
		return -ETIMEDOUT;
	}

	return ret;
}