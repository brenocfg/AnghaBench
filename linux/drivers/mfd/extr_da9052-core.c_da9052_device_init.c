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
typedef  int /*<<< orphan*/  u8 ;
struct da9052_pdata {int /*<<< orphan*/  (* init ) (struct da9052*) ;} ;
struct da9052 {int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  done; int /*<<< orphan*/  auxadc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int da9052_clear_fault_log (struct da9052*) ; 
 int /*<<< orphan*/  da9052_irq_exit (struct da9052*) ; 
 int da9052_irq_init (struct da9052*) ; 
 int /*<<< orphan*/  da9052_subdev_info ; 
 int /*<<< orphan*/  da9052_tsi_subdev_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9052_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct da9052*) ; 

int da9052_device_init(struct da9052 *da9052, u8 chip_id)
{
	struct da9052_pdata *pdata = dev_get_platdata(da9052->dev);
	int ret;

	mutex_init(&da9052->auxadc_lock);
	init_completion(&da9052->done);

	ret = da9052_clear_fault_log(da9052);
	if (ret < 0)
		dev_warn(da9052->dev, "Cannot clear FAULT_LOG\n");

	if (pdata && pdata->init != NULL)
		pdata->init(da9052);

	da9052->chip_id = chip_id;

	ret = da9052_irq_init(da9052);
	if (ret != 0) {
		dev_err(da9052->dev, "da9052_irq_init failed: %d\n", ret);
		return ret;
	}

	ret = mfd_add_devices(da9052->dev, PLATFORM_DEVID_AUTO,
			      da9052_subdev_info,
			      ARRAY_SIZE(da9052_subdev_info), NULL, 0, NULL);
	if (ret) {
		dev_err(da9052->dev, "mfd_add_devices failed: %d\n", ret);
		goto err;
	}

	/*
	 * Check if touchscreen pins are used are analogue input instead
	 * of having a touchscreen connected to them. The analogue input
	 * functionality will be provided by hwmon driver (if enabled).
	 */
	if (!device_property_read_bool(da9052->dev, "dlg,tsi-as-adc")) {
		ret = mfd_add_devices(da9052->dev, PLATFORM_DEVID_AUTO,
				      da9052_tsi_subdev_info,
				      ARRAY_SIZE(da9052_tsi_subdev_info),
				      NULL, 0, NULL);
		if (ret) {
			dev_err(da9052->dev, "failed to add TSI subdev: %d\n",
				ret);
			goto err;
		}
	}

	return 0;

err:
	mfd_remove_devices(da9052->dev);
	da9052_irq_exit(da9052);

	return ret;
}