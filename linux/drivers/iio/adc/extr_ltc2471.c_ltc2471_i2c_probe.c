#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ltc2471_data {struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ltc2471_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ltc2471_channel ; 
 int ltc2471_get_value (struct i2c_client*) ; 
 int /*<<< orphan*/  ltc2471_info ; 
 scalar_t__ ltc2473 ; 
 int /*<<< orphan*/  ltc2473_channel ; 

__attribute__((used)) static int ltc2471_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ltc2471_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = id->name;
	indio_dev->info = &ltc2471_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	if (id->driver_data == ltc2473)
		indio_dev->channels = ltc2473_channel;
	else
		indio_dev->channels = ltc2471_channel;
	indio_dev->num_channels = 1;

	/* Trigger once to start conversion and check if chip is there */
	ret = ltc2471_get_value(client);
	if (ret < 0) {
		dev_err(&client->dev, "Cannot read from device.\n");
		return ret;
	}

	return devm_iio_device_register(&client->dev, indio_dev);
}