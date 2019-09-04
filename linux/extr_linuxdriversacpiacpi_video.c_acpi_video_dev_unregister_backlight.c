#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct acpi_video_device {TYPE_4__* cooling_dev; TYPE_2__* dev; TYPE_5__* brightness; int /*<<< orphan*/ * backlight; } ;
struct TYPE_10__ {struct TYPE_10__* levels; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_3__ device; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (TYPE_4__*) ; 

__attribute__((used)) static void acpi_video_dev_unregister_backlight(struct acpi_video_device *device)
{
	if (device->backlight) {
		backlight_device_unregister(device->backlight);
		device->backlight = NULL;
	}
	if (device->brightness) {
		kfree(device->brightness->levels);
		kfree(device->brightness);
		device->brightness = NULL;
	}
	if (device->cooling_dev) {
		sysfs_remove_link(&device->dev->dev.kobj, "thermal_cooling");
		sysfs_remove_link(&device->cooling_dev->device.kobj, "device");
		thermal_cooling_device_unregister(device->cooling_dev);
		device->cooling_dev = NULL;
	}
}