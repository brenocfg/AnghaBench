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
struct msm_iommu_dev {int /*<<< orphan*/  iommu; } ;
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 struct msm_iommu_dev* find_iommu_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  msm_iommu_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int msm_iommu_add_device(struct device *dev)
{
	struct msm_iommu_dev *iommu;
	struct iommu_group *group;
	unsigned long flags;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	iommu = find_iommu_for_dev(dev);
	spin_unlock_irqrestore(&msm_iommu_lock, flags);

	if (iommu)
		iommu_device_link(&iommu->iommu, dev);
	else
		return -ENODEV;

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);

	iommu_group_put(group);

	return 0;
}