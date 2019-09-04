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
struct iommu_group {int /*<<< orphan*/  devices_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 

void iommu_group_put(struct iommu_group *group)
{
	if (group)
		kobject_put(group->devices_kobj);
}