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
struct iommu_fwspec {struct arm_smmu_master_data* iommu_priv; int /*<<< orphan*/ * ops; } ;
struct device {struct iommu_fwspec* iommu_fwspec; } ;
struct TYPE_2__ {scalar_t__ assigned; } ;
struct arm_smmu_master_data {TYPE_1__ ste; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_detach_dev (struct device*) ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_fwspec_free (struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct arm_smmu_master_data*) ; 

__attribute__((used)) static void arm_smmu_remove_device(struct device *dev)
{
	struct iommu_fwspec *fwspec = dev->iommu_fwspec;
	struct arm_smmu_master_data *master;
	struct arm_smmu_device *smmu;

	if (!fwspec || fwspec->ops != &arm_smmu_ops)
		return;

	master = fwspec->iommu_priv;
	smmu = master->smmu;
	if (master && master->ste.assigned)
		arm_smmu_detach_dev(dev);
	iommu_group_remove_device(dev);
	iommu_device_unlink(&smmu->iommu, dev);
	kfree(master);
	iommu_fwspec_free(dev);
}