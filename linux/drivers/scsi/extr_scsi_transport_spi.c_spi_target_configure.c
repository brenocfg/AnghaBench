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
struct transport_container {int dummy; } ;
struct kobject {int dummy; } ;
struct device {struct kobject kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_update_group (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_attribute_group ; 

__attribute__((used)) static int spi_target_configure(struct transport_container *tc,
				struct device *dev,
				struct device *cdev)
{
	struct kobject *kobj = &cdev->kobj;

	/* force an update based on parameters read from the device */
	sysfs_update_group(kobj, &target_attribute_group);

	return 0;
}