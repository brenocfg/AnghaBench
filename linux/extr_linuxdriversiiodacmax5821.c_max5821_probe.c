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
typedef  size_t u32 ;
struct max5821_data {int* powerdown; int vref_mv; int /*<<< orphan*/  vref_reg; int /*<<< orphan*/ * powerdown_mode; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX5821_100KOHM_TO_GND ; 
 size_t MAX5821_MAX_DAC_CHANNELS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct max5821_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max5821_channels ; 
 int /*<<< orphan*/  max5821_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max5821_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct max5821_data *data;
	struct iio_dev *indio_dev;
	u32 tmp;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	/* max5821 start in powerdown mode 100Kohm to ground */
	for (tmp = 0; tmp < MAX5821_MAX_DAC_CHANNELS; tmp++) {
		data->powerdown[tmp] = true;
		data->powerdown_mode[tmp] = MAX5821_100KOHM_TO_GND;
	}

	data->vref_reg = devm_regulator_get(&client->dev, "vref");
	if (IS_ERR(data->vref_reg)) {
		ret = PTR_ERR(data->vref_reg);
		dev_err(&client->dev,
			"Failed to get vref regulator: %d\n", ret);
		goto error_free_reg;
	}

	ret = regulator_enable(data->vref_reg);
	if (ret) {
		dev_err(&client->dev,
			"Failed to enable vref regulator: %d\n", ret);
		goto error_free_reg;
	}

	ret = regulator_get_voltage(data->vref_reg);
	if (ret < 0) {
		dev_err(&client->dev,
			"Failed to get voltage on regulator: %d\n", ret);
		goto error_disable_reg;
	}

	data->vref_mv = ret / 1000;

	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->num_channels = ARRAY_SIZE(max5821_channels);
	indio_dev->channels = max5821_channels;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &max5821_info;

	return iio_device_register(indio_dev);

error_disable_reg:
	regulator_disable(data->vref_reg);

error_free_reg:

	return ret;
}