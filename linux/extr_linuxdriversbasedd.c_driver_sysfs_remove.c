#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_driver {TYPE_1__* p; scalar_t__ coredump; } ;
struct device {int /*<<< orphan*/  kobj; struct device_driver* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_coredump ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 char* kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void driver_sysfs_remove(struct device *dev)
{
	struct device_driver *drv = dev->driver;

	if (drv) {
		if (drv->coredump)
			device_remove_file(dev, &dev_attr_coredump);
		sysfs_remove_link(&drv->p->kobj, kobject_name(&dev->kobj));
		sysfs_remove_link(&dev->kobj, "driver");
	}
}