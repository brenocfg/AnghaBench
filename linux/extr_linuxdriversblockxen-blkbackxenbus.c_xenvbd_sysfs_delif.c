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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct xenbus_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_mode ; 
 int /*<<< orphan*/  dev_attr_physical_device ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_vbdstat_group ; 

__attribute__((used)) static void xenvbd_sysfs_delif(struct xenbus_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &xen_vbdstat_group);
	device_remove_file(&dev->dev, &dev_attr_mode);
	device_remove_file(&dev->dev, &dev_attr_physical_device);
}