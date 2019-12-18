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
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct hp206c_data {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  HP206C_CMD_SOFT_RST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hp206c_set_compensation (struct i2c_client*,int) ; 
 int hp206c_wait_dev_rdy (struct iio_dev*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct hp206c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hp206c_soft_reset(struct iio_dev *indio_dev)
{
	int ret;
	struct hp206c_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;

	ret = i2c_smbus_write_byte(client, HP206C_CMD_SOFT_RST);
	if (ret) {
		dev_err(&client->dev, "Failed to reset device: %d\n", ret);
		return ret;
	}

	usleep_range(400, 600);

	ret = hp206c_wait_dev_rdy(indio_dev);
	if (ret) {
		dev_err(&client->dev, "Device not ready after soft reset: %d\n", ret);
		return ret;
	}

	ret = hp206c_set_compensation(client, true);
	if (ret)
		dev_err(&client->dev, "Failed to enable compensation: %d\n", ret);
	return ret;
}