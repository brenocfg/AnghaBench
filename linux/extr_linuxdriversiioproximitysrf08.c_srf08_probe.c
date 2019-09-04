#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct srf08_data {int sensor_type; TYPE_2__* chip_info; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
typedef  enum srf08_sensor_type { ____Placeholder_srf08_sensor_type } srf08_sensor_type ;
struct TYPE_6__ {scalar_t__ sensitivity_default; scalar_t__ range_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
#define  SRF02 130 
#define  SRF08 129 
#define  SRF10 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct srf08_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__ srf02_chip_info ; 
 int /*<<< orphan*/  srf02_info ; 
 int /*<<< orphan*/  srf08_channels ; 
 TYPE_2__ srf08_chip_info ; 
 int /*<<< orphan*/  srf08_info ; 
 int /*<<< orphan*/  srf08_trigger_handler ; 
 int srf08_write_range_mm (struct srf08_data*,scalar_t__) ; 
 int srf08_write_sensitivity (struct srf08_data*,scalar_t__) ; 
 TYPE_2__ srf10_chip_info ; 

__attribute__((used)) static int srf08_probe(struct i2c_client *client,
					 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct srf08_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_BYTE_DATA |
					I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
					I2C_FUNC_SMBUS_READ_WORD_DATA))
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->sensor_type = (enum srf08_sensor_type)id->driver_data;

	switch (data->sensor_type) {
	case SRF02:
		data->chip_info = &srf02_chip_info;
		indio_dev->info = &srf02_info;
		break;
	case SRF08:
		data->chip_info = &srf08_chip_info;
		indio_dev->info = &srf08_info;
		break;
	case SRF10:
		data->chip_info = &srf10_chip_info;
		indio_dev->info = &srf08_info;
		break;
	default:
		return -EINVAL;
	}

	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = srf08_channels;
	indio_dev->num_channels = ARRAY_SIZE(srf08_channels);

	mutex_init(&data->lock);

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
			iio_pollfunc_store_time, srf08_trigger_handler, NULL);
	if (ret < 0) {
		dev_err(&client->dev, "setup of iio triggered buffer failed\n");
		return ret;
	}

	if (data->chip_info->range_default) {
		/*
		 * set default range of device in mm here
		 * these register values cannot be read from the hardware
		 * therefore set driver specific default values
		 *
		 * srf02 don't have a default value so it'll be omitted
		 */
		ret = srf08_write_range_mm(data,
					data->chip_info->range_default);
		if (ret < 0)
			return ret;
	}

	if (data->chip_info->sensitivity_default) {
		/*
		 * set default sensitivity of device here
		 * these register values cannot be read from the hardware
		 * therefore set driver specific default values
		 *
		 * srf02 don't have a default value so it'll be omitted
		 */
		ret = srf08_write_sensitivity(data,
				data->chip_info->sensitivity_default);
		if (ret < 0)
			return ret;
	}

	return devm_iio_device_register(&client->dev, indio_dev);
}