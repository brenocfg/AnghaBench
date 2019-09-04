#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct acpi_fan {TYPE_3__* cdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_2__ device; } ;

/* Variables and functions */
 struct acpi_fan* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (TYPE_3__*) ; 

__attribute__((used)) static int acpi_fan_remove(struct platform_device *pdev)
{
	struct acpi_fan *fan = platform_get_drvdata(pdev);

	sysfs_remove_link(&pdev->dev.kobj, "thermal_cooling");
	sysfs_remove_link(&fan->cdev->device.kobj, "device");
	thermal_cooling_device_unregister(fan->cdev);

	return 0;
}