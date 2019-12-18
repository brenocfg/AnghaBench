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
struct mdev_type {int /*<<< orphan*/ * devices_kobj; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mdev_device_attrs ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void mdev_remove_sysfs_files(struct device *dev, struct mdev_type *type)
{
	sysfs_remove_files(&dev->kobj, mdev_device_attrs);
	sysfs_remove_link(&dev->kobj, "mdev_type");
	sysfs_remove_link(type->devices_kobj, dev_name(dev));
}