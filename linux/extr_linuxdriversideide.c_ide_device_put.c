#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gendev; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void ide_device_put(ide_drive_t *drive)
{
#ifdef CONFIG_MODULE_UNLOAD
	struct device *host_dev = drive->hwif->host->dev[0];
	struct module *module = host_dev ? host_dev->driver->owner : NULL;

	module_put(module);
#endif
	put_device(&drive->gendev);
}