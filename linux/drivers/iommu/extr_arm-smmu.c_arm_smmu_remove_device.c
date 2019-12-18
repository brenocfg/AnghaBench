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
struct iommu_fwspec {struct arm_smmu_master_cfg* iommu_priv; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct arm_smmu_master_cfg {struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_master_free_smes (struct iommu_fwspec*) ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 int arm_smmu_rpm_get (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_rpm_put (struct arm_smmu_device*) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_fwspec_free (struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct arm_smmu_master_cfg*) ; 

__attribute__((used)) static void arm_smmu_remove_device(struct device *dev)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct arm_smmu_master_cfg *cfg;
	struct arm_smmu_device *smmu;
	int ret;

	if (!fwspec || fwspec->ops != &arm_smmu_ops)
		return;

	cfg  = fwspec->iommu_priv;
	smmu = cfg->smmu;

	ret = arm_smmu_rpm_get(smmu);
	if (ret < 0)
		return;

	iommu_device_unlink(&smmu->iommu, dev);
	arm_smmu_master_free_smes(fwspec);

	arm_smmu_rpm_put(smmu);

	iommu_group_remove_device(dev);
	kfree(fwspec->iommu_priv);
	iommu_fwspec_free(dev);
}