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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct hp206c_data {int /*<<< orphan*/  mutex; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  hp206c_channels ; 
 int /*<<< orphan*/  hp206c_info ; 
 int hp206c_soft_reset (struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct hp206c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp206c_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct hp206c_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
		dev_err(&client->dev, "Adapter does not support "
				"all required i2c functionality\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->mutex);

	indio_dev->info = &hp206c_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = hp206c_channels;
	indio_dev->num_channels = ARRAY_SIZE(hp206c_channels);

	i2c_set_clientdata(client, indio_dev);

	/* Do a soft reset on probe */
	ret = hp206c_soft_reset(indio_dev);
	if (ret) {
		dev_err(&client->dev, "Failed to reset on startup: %d\n", ret);
		return -ENODEV;
	}

	return devm_iio_device_register(&client->dev, indio_dev);
}