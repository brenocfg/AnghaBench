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
struct iommu_group {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __iommu_group_for_each_dev (struct iommu_group*,void*,int (*) (struct device*,void*)) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iommu_group_for_each_dev(struct iommu_group *group, void *data,
			     int (*fn)(struct device *, void *))
{
	int ret;

	mutex_lock(&group->mutex);
	ret = __iommu_group_for_each_dev(group, data, fn);
	mutex_unlock(&group->mutex);

	return ret;
}