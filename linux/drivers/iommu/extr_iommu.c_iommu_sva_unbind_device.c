#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iommu_sva {struct device* dev; } ;
struct iommu_ops {int /*<<< orphan*/  (* sva_unbind ) (struct iommu_sva*) ;} ;
struct iommu_group {int /*<<< orphan*/  mutex; } ;
struct device {TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 struct iommu_group* iommu_group_get (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iommu_sva*) ; 

void iommu_sva_unbind_device(struct iommu_sva *handle)
{
	struct iommu_group *group;
	struct device *dev = handle->dev;
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (!ops || !ops->sva_unbind)
		return;

	group = iommu_group_get(dev);
	if (!group)
		return;

	mutex_lock(&group->mutex);
	ops->sva_unbind(handle);
	mutex_unlock(&group->mutex);

	iommu_group_put(group);
}