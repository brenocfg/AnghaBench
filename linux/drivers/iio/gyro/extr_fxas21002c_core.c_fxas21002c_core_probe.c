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
struct regmap_field {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct fxas21002c_data {int irq; int /*<<< orphan*/  lock; struct regmap_field** regmap_fields; struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int F_MAX_FIELDS ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regmap_field*) ; 
 int PTR_ERR (struct regmap_field*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct fxas21002c_data*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap_field* devm_regmap_field_alloc (struct device*,struct regmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxas21002c_channels ; 
 int fxas21002c_chip_init (struct fxas21002c_data*) ; 
 int /*<<< orphan*/  fxas21002c_info ; 
 int /*<<< orphan*/  fxas21002c_power_disable_action ; 
 int fxas21002c_power_enable (struct fxas21002c_data*) ; 
 int /*<<< orphan*/ * fxas21002c_reg_fields ; 
 int fxas21002c_regulators_get (struct fxas21002c_data*) ; 
 int /*<<< orphan*/  fxas21002c_trigger_handler ; 
 int fxas21002c_trigger_probe (struct fxas21002c_data*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct fxas21002c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

int fxas21002c_core_probe(struct device *dev, struct regmap *regmap, int irq,
			  const char *name)
{
	struct fxas21002c_data *data;
	struct iio_dev *indio_dev;
	struct regmap_field *f;
	int i;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->irq = irq;
	data->regmap = regmap;

	for (i = 0; i < F_MAX_FIELDS; i++) {
		f = devm_regmap_field_alloc(dev, data->regmap,
					    fxas21002c_reg_fields[i]);
		if (IS_ERR(f))
			return PTR_ERR(f);

		data->regmap_fields[i] = f;
	}

	mutex_init(&data->lock);

	ret = fxas21002c_regulators_get(data);
	if (ret < 0)
		return ret;

	ret = fxas21002c_power_enable(data);
	if (ret < 0)
		return ret;

	ret = devm_add_action_or_reset(dev, fxas21002c_power_disable_action,
				       data);
	if (ret < 0)
		return ret;

	ret = fxas21002c_chip_init(data);
	if (ret < 0)
		return ret;

	indio_dev->dev.parent = dev;
	indio_dev->channels = fxas21002c_channels;
	indio_dev->num_channels = ARRAY_SIZE(fxas21002c_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &fxas21002c_info;

	ret = fxas21002c_trigger_probe(data);
	if (ret < 0)
		return ret;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, NULL,
					      fxas21002c_trigger_handler, NULL);
	if (ret < 0)
		return ret;

	ret = pm_runtime_set_active(dev);
	if (ret)
		return ret;

	pm_runtime_enable(dev);
	pm_runtime_set_autosuspend_delay(dev, 2000);
	pm_runtime_use_autosuspend(dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto pm_disable;

	return 0;

pm_disable:
	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);

	return ret;
}