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
struct veml6070_data {int config; int /*<<< orphan*/  client2; struct i2c_client* client1; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEML6070_ADDR_DATA_LSB ; 
 int VEML6070_COMMAND_RSRVD ; 
 int VEML6070_COMMAND_SD ; 
 int /*<<< orphan*/  VEML6070_DRV_NAME ; 
 int VEML6070_IT_10 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct veml6070_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  veml6070_channels ; 
 int /*<<< orphan*/  veml6070_info ; 

__attribute__((used)) static int veml6070_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct veml6070_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client1 = client;
	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &veml6070_info;
	indio_dev->channels = veml6070_channels;
	indio_dev->num_channels = ARRAY_SIZE(veml6070_channels);
	indio_dev->name = VEML6070_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	data->client2 = i2c_new_dummy_device(client->adapter, VEML6070_ADDR_DATA_LSB);
	if (IS_ERR(data->client2)) {
		dev_err(&client->dev, "i2c device for second chip address failed\n");
		return PTR_ERR(data->client2);
	}

	data->config = VEML6070_IT_10 | VEML6070_COMMAND_RSRVD |
		VEML6070_COMMAND_SD;
	ret = i2c_smbus_write_byte(data->client1, data->config);
	if (ret < 0)
		goto fail;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto fail;

	return ret;

fail:
	i2c_unregister_device(data->client2);
	return ret;
}