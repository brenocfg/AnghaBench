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
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 TYPE_1__ cpuidle_attr_group ; 
 int /*<<< orphan*/  cpuidle_switch_attrs ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ sysfs_switch ; 

int cpuidle_add_interface(struct device *dev)
{
	if (sysfs_switch)
		cpuidle_attr_group.attrs = cpuidle_switch_attrs;

	return sysfs_create_group(&dev->kobj, &cpuidle_attr_group);
}