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
struct vcnl4035_data {struct regmap* regmap; struct i2c_client* client; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  VCNL4035_DRV_NAME ; 
 int /*<<< orphan*/  VCNL4035_MODE_ALS_DISABLE ; 
 int /*<<< orphan*/  VCNL4035_SLEEP_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct vcnl4035_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcnl4035_channels ; 
 int /*<<< orphan*/  vcnl4035_info ; 
 int vcnl4035_init (struct vcnl4035_data*) ; 
 int vcnl4035_probe_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  vcnl4035_regmap_config ; 
 int /*<<< orphan*/  vcnl4035_set_als_power_state (struct vcnl4035_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcnl4035_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct vcnl4035_data *data;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &vcnl4035_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "regmap_init failed!\n");
		return PTR_ERR(regmap);
	}

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &vcnl4035_info;
	indio_dev->name = VCNL4035_DRV_NAME;
	indio_dev->channels = vcnl4035_channels;
	indio_dev->num_channels = ARRAY_SIZE(vcnl4035_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = vcnl4035_init(data);
	if (ret < 0) {
		dev_err(&client->dev, "vcnl4035 chip init failed\n");
		return ret;
	}

	if (client->irq > 0) {
		ret = vcnl4035_probe_trigger(indio_dev);
		if (ret < 0) {
			dev_err(&client->dev, "vcnl4035 unable init trigger\n");
			goto fail_poweroff;
		}
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0)
		goto fail_poweroff;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto fail_poweroff;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, VCNL4035_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	return 0;

fail_poweroff:
	vcnl4035_set_als_power_state(data, VCNL4035_MODE_ALS_DISABLE);
	return ret;
}