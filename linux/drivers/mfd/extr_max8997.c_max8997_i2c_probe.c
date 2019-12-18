#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ of_node; } ;
struct max8997_platform_data {int /*<<< orphan*/  adapter; int /*<<< orphan*/  ono; int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct max8997_dev {struct max8997_platform_data* rtc; struct max8997_platform_data* haptic; struct max8997_platform_data* muic; TYPE_1__* dev; int /*<<< orphan*/  iolock; int /*<<< orphan*/  ono; struct max8997_platform_data* pdata; int /*<<< orphan*/  irq; int /*<<< orphan*/  type; struct max8997_platform_data* i2c; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  ono; int /*<<< orphan*/  irq; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_ADDR_HAPTIC ; 
 int /*<<< orphan*/  I2C_ADDR_MUIC ; 
 int /*<<< orphan*/  I2C_ADDR_RTC ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct max8997_platform_data*) ; 
 int PTR_ERR (struct max8997_platform_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max8997_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct max8997_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct max8997_platform_data*,struct max8997_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct max8997_platform_data*) ; 
 int /*<<< orphan*/  max8997_devs ; 
 int /*<<< orphan*/  max8997_i2c_get_driver_data (struct max8997_platform_data*,struct i2c_device_id const*) ; 
 struct max8997_platform_data* max8997_i2c_parse_dt_pdata (TYPE_1__*) ; 
 int /*<<< orphan*/  max8997_irq_init (struct max8997_dev*) ; 
 int mfd_add_devices (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 

__attribute__((used)) static int max8997_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct max8997_dev *max8997;
	struct max8997_platform_data *pdata = dev_get_platdata(&i2c->dev);
	int ret = 0;

	max8997 = devm_kzalloc(&i2c->dev, sizeof(struct max8997_dev),
				GFP_KERNEL);
	if (max8997 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max8997);
	max8997->dev = &i2c->dev;
	max8997->i2c = i2c;
	max8997->type = max8997_i2c_get_driver_data(i2c, id);
	max8997->irq = i2c->irq;

	if (IS_ENABLED(CONFIG_OF) && max8997->dev->of_node) {
		pdata = max8997_i2c_parse_dt_pdata(max8997->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	if (!pdata)
		return ret;

	max8997->pdata = pdata;
	max8997->ono = pdata->ono;

	mutex_init(&max8997->iolock);

	max8997->rtc = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_RTC);
	if (IS_ERR(max8997->rtc)) {
		dev_err(max8997->dev, "Failed to allocate I2C device for RTC\n");
		return PTR_ERR(max8997->rtc);
	}
	i2c_set_clientdata(max8997->rtc, max8997);

	max8997->haptic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_HAPTIC);
	if (IS_ERR(max8997->haptic)) {
		dev_err(max8997->dev, "Failed to allocate I2C device for Haptic\n");
		ret = PTR_ERR(max8997->haptic);
		goto err_i2c_haptic;
	}
	i2c_set_clientdata(max8997->haptic, max8997);

	max8997->muic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_MUIC);
	if (IS_ERR(max8997->muic)) {
		dev_err(max8997->dev, "Failed to allocate I2C device for MUIC\n");
		ret = PTR_ERR(max8997->muic);
		goto err_i2c_muic;
	}
	i2c_set_clientdata(max8997->muic, max8997);

	pm_runtime_set_active(max8997->dev);

	max8997_irq_init(max8997);

	ret = mfd_add_devices(max8997->dev, -1, max8997_devs,
			ARRAY_SIZE(max8997_devs),
			NULL, 0, NULL);
	if (ret < 0) {
		dev_err(max8997->dev, "failed to add MFD devices %d\n", ret);
		goto err_mfd;
	}

	/*
	 * TODO: enable others (flash, muic, rtc, battery, ...) and
	 * check the return value
	 */

	/* MAX8997 has a power button input. */
	device_init_wakeup(max8997->dev, true);

	return ret;

err_mfd:
	mfd_remove_devices(max8997->dev);
	i2c_unregister_device(max8997->muic);
err_i2c_muic:
	i2c_unregister_device(max8997->haptic);
err_i2c_haptic:
	i2c_unregister_device(max8997->rtc);
	return ret;
}