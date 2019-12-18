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
struct serdev_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int acpi_serdev_register_devices (struct serdev_controller*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_registered ; 
 int of_serdev_register_devices (struct serdev_controller*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 

int serdev_controller_add(struct serdev_controller *ctrl)
{
	int ret_of, ret_acpi, ret;

	/* Can't register until after driver model init */
	if (WARN_ON(!is_registered))
		return -EAGAIN;

	ret = device_add(&ctrl->dev);
	if (ret)
		return ret;

	pm_runtime_enable(&ctrl->dev);

	ret_of = of_serdev_register_devices(ctrl);
	ret_acpi = acpi_serdev_register_devices(ctrl);
	if (ret_of && ret_acpi) {
		dev_dbg(&ctrl->dev, "no devices registered: of:%d acpi:%d\n",
			ret_of, ret_acpi);
		ret = -ENODEV;
		goto err_rpm_disable;
	}

	dev_dbg(&ctrl->dev, "serdev%d registered: dev:%p\n",
		ctrl->nr, &ctrl->dev);
	return 0;

err_rpm_disable:
	pm_runtime_disable(&ctrl->dev);
	device_del(&ctrl->dev);
	return ret;
}