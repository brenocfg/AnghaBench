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
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void class_compat_remove_link(struct class_compat *cls, struct device *dev,
			      struct device *device_link)
{
	if (device_link)
		sysfs_remove_link(&dev->kobj, "device");
	sysfs_remove_link(cls->kobj, dev_name(dev));
}