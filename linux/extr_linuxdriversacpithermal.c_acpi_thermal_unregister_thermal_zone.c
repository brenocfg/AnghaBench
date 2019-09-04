#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_thermal {TYPE_3__* device; TYPE_4__* thermal_zone; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_2__ device; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_detach_private_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (TYPE_4__*) ; 

__attribute__((used)) static void acpi_thermal_unregister_thermal_zone(struct acpi_thermal *tz)
{
	sysfs_remove_link(&tz->device->dev.kobj, "thermal_zone");
	sysfs_remove_link(&tz->thermal_zone->device.kobj, "device");
	thermal_zone_device_unregister(tz->thermal_zone);
	tz->thermal_zone = NULL;
	acpi_bus_detach_private_data(tz->device->handle);
}