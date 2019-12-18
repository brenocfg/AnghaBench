#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; TYPE_2__* channels; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
struct ak8974 {int drdy_active_low; int drdy_irq; TYPE_2__* regs; int /*<<< orphan*/  name; int /*<<< orphan*/  map; int /*<<< orphan*/  orientation; int /*<<< orphan*/  lock; struct i2c_client* i2c; } ;
struct TYPE_8__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  AK8974_PWR_OFF ; 
 int /*<<< orphan*/  AK8974_PWR_ON ; 
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_2__* ak8974_channels ; 
 int ak8974_detect (struct ak8974*) ; 
 int /*<<< orphan*/  ak8974_drdy_irq ; 
 int /*<<< orphan*/  ak8974_drdy_irq_thread ; 
 int /*<<< orphan*/  ak8974_handle_trigger ; 
 int /*<<< orphan*/  ak8974_info ; 
 int /*<<< orphan*/  ak8974_reg_avdd ; 
 int /*<<< orphan*/  ak8974_reg_dvdd ; 
 int /*<<< orphan*/  ak8974_regmap_config ; 
 int ak8974_reset (struct ak8974*) ; 
 int /*<<< orphan*/  ak8974_scan_masks ; 
 int ak8974_selftest (struct ak8974*) ; 
 int ak8974_set_power (struct ak8974*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct ak8974*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ak8974* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int ak8974_probe(struct i2c_client *i2c,
			const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ak8974 *ak8974;
	unsigned long irq_trig;
	int irq = i2c->irq;
	int ret;

	/* Register with IIO */
	indio_dev = devm_iio_device_alloc(&i2c->dev, sizeof(*ak8974));
	if (indio_dev == NULL)
		return -ENOMEM;

	ak8974 = iio_priv(indio_dev);
	i2c_set_clientdata(i2c, indio_dev);
	ak8974->i2c = i2c;
	mutex_init(&ak8974->lock);

	ret = iio_read_mount_matrix(&i2c->dev, "mount-matrix",
				    &ak8974->orientation);
	if (ret)
		return ret;

	ak8974->regs[0].supply = ak8974_reg_avdd;
	ak8974->regs[1].supply = ak8974_reg_dvdd;

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(ak8974->regs),
				      ak8974->regs);
	if (ret < 0) {
		dev_err(&i2c->dev, "cannot get regulators\n");
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(ak8974->regs), ak8974->regs);
	if (ret < 0) {
		dev_err(&i2c->dev, "cannot enable regulators\n");
		return ret;
	}

	/* Take runtime PM online */
	pm_runtime_get_noresume(&i2c->dev);
	pm_runtime_set_active(&i2c->dev);
	pm_runtime_enable(&i2c->dev);

	ak8974->map = devm_regmap_init_i2c(i2c, &ak8974_regmap_config);
	if (IS_ERR(ak8974->map)) {
		dev_err(&i2c->dev, "failed to allocate register map\n");
		return PTR_ERR(ak8974->map);
	}

	ret = ak8974_set_power(ak8974, AK8974_PWR_ON);
	if (ret) {
		dev_err(&i2c->dev, "could not power on\n");
		goto power_off;
	}

	ret = ak8974_detect(ak8974);
	if (ret) {
		dev_err(&i2c->dev, "neither AK8974 nor AMI30x found\n");
		goto power_off;
	}

	ret = ak8974_selftest(ak8974);
	if (ret)
		dev_err(&i2c->dev, "selftest failed (continuing anyway)\n");

	ret = ak8974_reset(ak8974);
	if (ret) {
		dev_err(&i2c->dev, "AK8974 reset failed\n");
		goto power_off;
	}

	pm_runtime_set_autosuspend_delay(&i2c->dev,
					 AK8974_AUTOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(&i2c->dev);
	pm_runtime_put(&i2c->dev);

	indio_dev->dev.parent = &i2c->dev;
	indio_dev->channels = ak8974_channels;
	indio_dev->num_channels = ARRAY_SIZE(ak8974_channels);
	indio_dev->info = &ak8974_info;
	indio_dev->available_scan_masks = ak8974_scan_masks;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->name = ak8974->name;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 ak8974_handle_trigger,
					 NULL);
	if (ret) {
		dev_err(&i2c->dev, "triggered buffer setup failed\n");
		goto disable_pm;
	}

	/* If we have a valid DRDY IRQ, make use of it */
	if (irq > 0) {
		irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
		if (irq_trig == IRQF_TRIGGER_RISING) {
			dev_info(&i2c->dev, "enable rising edge DRDY IRQ\n");
		} else if (irq_trig == IRQF_TRIGGER_FALLING) {
			ak8974->drdy_active_low = true;
			dev_info(&i2c->dev, "enable falling edge DRDY IRQ\n");
		} else {
			irq_trig = IRQF_TRIGGER_RISING;
		}
		irq_trig |= IRQF_ONESHOT;
		irq_trig |= IRQF_SHARED;

		ret = devm_request_threaded_irq(&i2c->dev,
						irq,
						ak8974_drdy_irq,
						ak8974_drdy_irq_thread,
						irq_trig,
						ak8974->name,
						ak8974);
		if (ret) {
			dev_err(&i2c->dev, "unable to request DRDY IRQ "
				"- proceeding without IRQ\n");
			goto no_irq;
		}
		ak8974->drdy_irq = true;
	}

no_irq:
	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&i2c->dev, "device register failed\n");
		goto cleanup_buffer;
	}

	return 0;

cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
disable_pm:
	pm_runtime_put_noidle(&i2c->dev);
	pm_runtime_disable(&i2c->dev);
	ak8974_set_power(ak8974, AK8974_PWR_OFF);
power_off:
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	return ret;
}