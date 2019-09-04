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
struct max44000_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX44000_CFG_MODE_ALS_PRX ; 
 int MAX44000_CFG_TRIM ; 
 int /*<<< orphan*/  MAX44000_DRV_NAME ; 
 int /*<<< orphan*/  MAX44000_LED_CURRENT_DEFAULT ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_MAIN ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_RX ; 
 int MAX44000_REG_CFG_RX_DEFAULT ; 
 int /*<<< orphan*/  MAX44000_REG_STATUS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct max44000_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max44000_channels ; 
 int /*<<< orphan*/  max44000_info ; 
 int /*<<< orphan*/  max44000_regmap_config ; 
 int /*<<< orphan*/  max44000_trigger_handler ; 
 int max44000_write_led_current_raw (struct max44000_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max44000_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct max44000_data *data;
	struct iio_dev *indio_dev;
	int ret, reg;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);
	data->regmap = devm_regmap_init_i2c(client, &max44000_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(&client->dev, "regmap_init failed!\n");
		return PTR_ERR(data->regmap);
	}

	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &max44000_info;
	indio_dev->name = MAX44000_DRV_NAME;
	indio_dev->channels = max44000_channels;
	indio_dev->num_channels = ARRAY_SIZE(max44000_channels);

	/*
	 * The device doesn't have a reset function so we just clear some
	 * important bits at probe time to ensure sane operation.
	 *
	 * Since we don't support interrupts/events the threshold values are
	 * not important. We also don't touch trim values.
	 */

	/* Reset ALS scaling bits */
	ret = regmap_write(data->regmap, MAX44000_REG_CFG_RX,
			   MAX44000_REG_CFG_RX_DEFAULT);
	if (ret < 0) {
		dev_err(&client->dev, "failed to write default CFG_RX: %d\n",
			ret);
		return ret;
	}

	/*
	 * By default the LED pulse used for the proximity sensor is disabled.
	 * Set a middle value so that we get some sort of valid data by default.
	 */
	ret = max44000_write_led_current_raw(data, MAX44000_LED_CURRENT_DEFAULT);
	if (ret < 0) {
		dev_err(&client->dev, "failed to write init config: %d\n", ret);
		return ret;
	}

	/* Reset CFG bits to ALS_PRX mode which allows easy reading of both values. */
	reg = MAX44000_CFG_TRIM | MAX44000_CFG_MODE_ALS_PRX;
	ret = regmap_write(data->regmap, MAX44000_REG_CFG_MAIN, reg);
	if (ret < 0) {
		dev_err(&client->dev, "failed to write init config: %d\n", ret);
		return ret;
	}

	/* Read status at least once to clear any stale interrupt bits. */
	ret = regmap_read(data->regmap, MAX44000_REG_STATUS, &reg);
	if (ret < 0) {
		dev_err(&client->dev, "failed to read init status: %d\n", ret);
		return ret;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL, max44000_trigger_handler, NULL);
	if (ret < 0) {
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		return ret;
	}

	return iio_device_register(indio_dev);
}