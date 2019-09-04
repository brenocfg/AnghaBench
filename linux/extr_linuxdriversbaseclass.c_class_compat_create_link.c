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
struct class_compat {int /*<<< orphan*/ * kobj; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

int class_compat_create_link(struct class_compat *cls, struct device *dev,
			     struct device *device_link)
{
	int error;

	error = sysfs_create_link(cls->kobj, &dev->kobj, dev_name(dev));
	if (error)
		return error;

	/*
	 * Optionally add a "device" link (typically to the parent), as a
	 * class device would have one and we want to provide as much
	 * backwards compatibility as possible.
	 */
	if (device_link) {
		error = sysfs_create_link(&dev->kobj, &device_link->kobj,
					  "device");
		if (error)
			sysfs_remove_link(cls->kobj, dev_name(dev));
	}

	return error;
}