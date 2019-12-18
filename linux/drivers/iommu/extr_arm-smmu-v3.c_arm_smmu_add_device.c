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
typedef  int /*<<< orphan*/  u32 ;
struct iommu_group {int dummy; } ;
struct iommu_fwspec {int num_ids; struct arm_smmu_master* iommu_priv; int /*<<< orphan*/ * ids; int /*<<< orphan*/  iommu_fwnode; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct arm_smmu_master {int num_sids; int /*<<< orphan*/ * sids; struct arm_smmu_device* smmu; struct device* dev; } ;
struct arm_smmu_device {int features; int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_2_LVL_STRTAB ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct iommu_group*) ; 
 int PTR_ERR_OR_ZERO (struct iommu_group*) ; 
 scalar_t__ WARN_ON_ONCE (struct arm_smmu_master*) ; 
 struct arm_smmu_device* arm_smmu_get_by_fwnode (int /*<<< orphan*/ ) ; 
 int arm_smmu_init_l2_strtab (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 int /*<<< orphan*/  arm_smmu_sid_in_range (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 struct arm_smmu_master* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_add_device(struct device *dev)
{
	int i, ret;
	struct arm_smmu_device *smmu;
	struct arm_smmu_master *master;
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct iommu_group *group;

	if (!fwspec || fwspec->ops != &arm_smmu_ops)
		return -ENODEV;
	/*
	 * We _can_ actually withstand dodgy bus code re-calling add_device()
	 * without an intervening remove_device()/of_xlate() sequence, but
	 * we're not going to do so quietly...
	 */
	if (WARN_ON_ONCE(fwspec->iommu_priv)) {
		master = fwspec->iommu_priv;
		smmu = master->smmu;
	} else {
		smmu = arm_smmu_get_by_fwnode(fwspec->iommu_fwnode);
		if (!smmu)
			return -ENODEV;
		master = kzalloc(sizeof(*master), GFP_KERNEL);
		if (!master)
			return -ENOMEM;

		master->dev = dev;
		master->smmu = smmu;
		master->sids = fwspec->ids;
		master->num_sids = fwspec->num_ids;
		fwspec->iommu_priv = master;
	}

	/* Check the SIDs are in range of the SMMU and our stream table */
	for (i = 0; i < master->num_sids; i++) {
		u32 sid = master->sids[i];

		if (!arm_smmu_sid_in_range(smmu, sid))
			return -ERANGE;

		/* Ensure l2 strtab is initialised */
		if (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB) {
			ret = arm_smmu_init_l2_strtab(smmu, sid);
			if (ret)
				return ret;
		}
	}

	group = iommu_group_get_for_dev(dev);
	if (!IS_ERR(group)) {
		iommu_group_put(group);
		iommu_device_link(&smmu->iommu, dev);
	}

	return PTR_ERR_OR_ZERO(group);
}