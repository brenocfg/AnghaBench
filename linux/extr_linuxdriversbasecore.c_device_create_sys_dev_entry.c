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
struct kobject {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 struct kobject* device_to_dev_kobj (struct device*) ; 
 int /*<<< orphan*/  format_dev_t (char*,int /*<<< orphan*/ ) ; 
 int sysfs_create_link (struct kobject*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int device_create_sys_dev_entry(struct device *dev)
{
	struct kobject *kobj = device_to_dev_kobj(dev);
	int error = 0;
	char devt_str[15];

	if (kobj) {
		format_dev_t(devt_str, dev->devt);
		error = sysfs_create_link(kobj, &dev->kobj, devt_str);
	}

	return error;
}