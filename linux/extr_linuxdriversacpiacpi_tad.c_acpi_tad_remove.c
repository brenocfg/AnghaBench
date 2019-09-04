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
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct acpi_tad_driver_data {int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TAD_AC_TIMER ; 
 int /*<<< orphan*/  ACPI_TAD_DC_TIMER ; 
 int ACPI_TAD_DC_WAKE ; 
 int /*<<< orphan*/  acpi_tad_attr_group ; 
 int /*<<< orphan*/  acpi_tad_clear_status (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tad_dc_attr_group ; 
 int /*<<< orphan*/  acpi_tad_disable_timer (struct device*,int /*<<< orphan*/ ) ; 
 struct acpi_tad_driver_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_tad_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct acpi_tad_driver_data *dd = dev_get_drvdata(dev);

	device_init_wakeup(dev, false);

	pm_runtime_get_sync(dev);

	if (dd->capabilities & ACPI_TAD_DC_WAKE)
		sysfs_remove_group(&dev->kobj, &acpi_tad_dc_attr_group);

	sysfs_remove_group(&dev->kobj, &acpi_tad_attr_group);

	acpi_tad_disable_timer(dev, ACPI_TAD_AC_TIMER);
	acpi_tad_clear_status(dev, ACPI_TAD_AC_TIMER);
	if (dd->capabilities & ACPI_TAD_DC_WAKE) {
		acpi_tad_disable_timer(dev, ACPI_TAD_DC_TIMER);
		acpi_tad_clear_status(dev, ACPI_TAD_DC_TIMER);
	}

	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);
	return 0;
}