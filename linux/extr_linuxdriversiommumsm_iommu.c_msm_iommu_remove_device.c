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
struct device {int dummy; } ;

/* Variables and functions */
 struct msm_iommu_dev* find_iommu_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  msm_iommu_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msm_iommu_remove_device(struct device *dev)
{
	struct msm_iommu_dev *iommu;
	unsigned long flags;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	iommu = find_iommu_for_dev(dev);
	spin_unlock_irqrestore(&msm_iommu_lock, flags);

	if (iommu)
		iommu_device_unlink(&iommu->iommu, dev);

	iommu_group_remove_device(dev);
}