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
struct mm_struct {int dummy; } ;
struct iommu_sva {int dummy; } ;
struct iommu_ops {struct iommu_sva* (* sva_bind ) (struct device*,struct mm_struct*,void*) ;} ;
struct iommu_group {int /*<<< orphan*/  mutex; } ;
struct device {TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct iommu_sva* ERR_PTR (int /*<<< orphan*/ ) ; 
 int iommu_group_device_count (struct iommu_group*) ; 
 struct iommu_group* iommu_group_get (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iommu_sva* stub1 (struct device*,struct mm_struct*,void*) ; 

struct iommu_sva *
iommu_sva_bind_device(struct device *dev, struct mm_struct *mm, void *drvdata)
{
	struct iommu_group *group;
	struct iommu_sva *handle = ERR_PTR(-EINVAL);
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (!ops || !ops->sva_bind)
		return ERR_PTR(-ENODEV);

	group = iommu_group_get(dev);
	if (!group)
		return ERR_PTR(-ENODEV);

	/* Ensure device count and domain don't change while we're binding */
	mutex_lock(&group->mutex);

	/*
	 * To keep things simple, SVA currently doesn't support IOMMU groups
	 * with more than one device. Existing SVA-capable systems are not
	 * affected by the problems that required IOMMU groups (lack of ACS
	 * isolation, device ID aliasing and other hardware issues).
	 */
	if (iommu_group_device_count(group) != 1)
		goto out_unlock;

	handle = ops->sva_bind(dev, mm, drvdata);

out_unlock:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);

	return handle;
}