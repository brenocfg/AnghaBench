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
struct lidar_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lidar_smbus_xfer(struct lidar_data *data, u8 reg, u8 *val, int len)
{
	struct i2c_client *client = data->client;
	int ret;

	/*
	 * Device needs a STOP condition between address write, and data read
	 * so in turn i2c_smbus_read_byte_data cannot be used
	 */

	while (len--) {
		ret = i2c_smbus_write_byte(client, reg++);
		if (ret < 0) {
			dev_err(&client->dev, "cannot write addr value");
			return ret;
		}

		ret = i2c_smbus_read_byte(client);
		if (ret < 0) {
			dev_err(&client->dev, "cannot read data value");
			return ret;
		}

		*(val++) = ret;
	}

	return 0;
}