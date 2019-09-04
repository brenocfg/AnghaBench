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
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int sysfs_create_groups (int /*<<< orphan*/ *,struct attribute_group const**) ; 

int device_add_groups(struct device *dev, const struct attribute_group **groups)
{
	return sysfs_create_groups(&dev->kobj, groups);
}