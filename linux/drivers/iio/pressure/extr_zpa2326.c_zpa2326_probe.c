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
struct zpa2326_private {struct regmap* regmap; int /*<<< orphan*/  frequency; void* vdd; void* vref; } ;
struct regmap {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ZPA2326_DEVICE_ID_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (struct device*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct zpa2326_private* iio_priv (struct iio_dev*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  zpa2326_buffer_setup_ops ; 
 int zpa2326_config_oneshot (struct iio_dev*,int) ; 
 struct iio_dev* zpa2326_create_managed_iiodev (struct device*,char const*,struct regmap*) ; 
 int /*<<< orphan*/  zpa2326_fini_runtime (struct device*) ; 
 int /*<<< orphan*/  zpa2326_highest_frequency () ; 
 int zpa2326_init_managed_irq (struct device*,struct iio_dev*,struct zpa2326_private*,int) ; 
 int zpa2326_init_managed_trigger (struct device*,struct iio_dev*,struct zpa2326_private*,int) ; 
 int /*<<< orphan*/  zpa2326_init_runtime (struct device*) ; 
 int /*<<< orphan*/  zpa2326_power_off (struct iio_dev*,struct zpa2326_private*) ; 
 int zpa2326_power_on (struct iio_dev*,struct zpa2326_private*) ; 
 int zpa2326_sleep (struct iio_dev*) ; 
 int /*<<< orphan*/  zpa2326_trigger_handler ; 

int zpa2326_probe(struct device *parent,
		  const char    *name,
		  int            irq,
		  unsigned int   hwid,
		  struct regmap *regmap)
{
	struct iio_dev         *indio_dev;
	struct zpa2326_private *priv;
	int                     err;
	unsigned int            id;

	indio_dev = zpa2326_create_managed_iiodev(parent, name, regmap);
	if (!indio_dev)
		return -ENOMEM;

	priv = iio_priv(indio_dev);

	priv->vref = devm_regulator_get(parent, "vref");
	if (IS_ERR(priv->vref))
		return PTR_ERR(priv->vref);

	priv->vdd = devm_regulator_get(parent, "vdd");
	if (IS_ERR(priv->vdd))
		return PTR_ERR(priv->vdd);

	/* Set default hardware sampling frequency to highest rate supported. */
	priv->frequency = zpa2326_highest_frequency();

	/*
	 * Plug device's underlying bus abstraction : this MUST be set before
	 * registering interrupt handlers since an interrupt might happen if
	 * power up sequence is not properly applied.
	 */
	priv->regmap = regmap;

	err = devm_iio_triggered_buffer_setup(parent, indio_dev, NULL,
					      zpa2326_trigger_handler,
					      &zpa2326_buffer_setup_ops);
	if (err)
		return err;

	err = zpa2326_init_managed_trigger(parent, indio_dev, priv, irq);
	if (err)
		return err;

	err = zpa2326_init_managed_irq(parent, indio_dev, priv, irq);
	if (err)
		return err;

	/* Power up to check device ID and perform initial hardware setup. */
	err = zpa2326_power_on(indio_dev, priv);
	if (err)
		return err;

	/* Read id register to check we are talking to the right slave. */
	err = regmap_read(regmap, ZPA2326_DEVICE_ID_REG, &id);
	if (err)
		goto sleep;

	if (id != hwid) {
		dev_err(parent, "found device with unexpected id %02x", id);
		err = -ENODEV;
		goto sleep;
	}

	err = zpa2326_config_oneshot(indio_dev, irq);
	if (err)
		goto sleep;

	/* Setup done : go sleeping. Device will be awaken upon user request. */
	err = zpa2326_sleep(indio_dev);
	if (err)
		goto poweroff;

	dev_set_drvdata(parent, indio_dev);

	zpa2326_init_runtime(parent);

	err = iio_device_register(indio_dev);
	if (err) {
		zpa2326_fini_runtime(parent);
		goto poweroff;
	}

	return 0;

sleep:
	/* Put to sleep just in case power regulators are "dummy" ones. */
	zpa2326_sleep(indio_dev);
poweroff:
	zpa2326_power_off(indio_dev, priv);

	return err;
}