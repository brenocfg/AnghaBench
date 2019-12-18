#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fujitsu_laptop {TYPE_2__* pf_device; } ;
struct acpi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct fujitsu_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  fujitsu_pf_attribute_group ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fujitsu_laptop_platform_remove(struct acpi_device *device)
{
	struct fujitsu_laptop *priv = acpi_driver_data(device);

	sysfs_remove_group(&priv->pf_device->dev.kobj,
			   &fujitsu_pf_attribute_group);
	platform_device_unregister(priv->pf_device);
}