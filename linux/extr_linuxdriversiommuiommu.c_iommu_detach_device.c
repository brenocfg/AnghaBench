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
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __iommu_detach_group (struct iommu_domain*,struct iommu_group*) ; 
 int iommu_group_device_count (struct iommu_group*) ; 
 struct iommu_group* iommu_group_get (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iommu_detach_device(struct iommu_domain *domain, struct device *dev)
{
	struct iommu_group *group;

	group = iommu_group_get(dev);
	if (!group)
		return;

	mutex_lock(&group->mutex);
	if (iommu_group_device_count(group) != 1) {
		WARN_ON(1);
		goto out_unlock;
	}

	__iommu_detach_group(domain, group);

out_unlock:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);
}