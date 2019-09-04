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
struct iommu_domain {int dummy; } ;
struct device {TYPE_1__* iommu_fwspec; } ;
struct arm_smmu_strtab_ent {int assigned; int /*<<< orphan*/ * s2_cfg; int /*<<< orphan*/ * s1_cfg; } ;
struct arm_smmu_master_data {struct arm_smmu_strtab_ent ste; struct arm_smmu_device* smmu; } ;
struct arm_smmu_domain {scalar_t__ stage; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  s2_cfg; int /*<<< orphan*/  s1_cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct arm_smmu_master_data* iommu_priv; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_DOMAIN_BYPASS ; 
 scalar_t__ ARM_SMMU_DOMAIN_S1 ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  arm_smmu_detach_dev (struct device*) ; 
 int arm_smmu_domain_finalise (struct iommu_domain*) ; 
 int /*<<< orphan*/  arm_smmu_install_ste_for_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  arm_smmu_write_ctx_desc (struct arm_smmu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int arm_smmu_attach_dev(struct iommu_domain *domain, struct device *dev)
{
	int ret = 0;
	struct arm_smmu_device *smmu;
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	struct arm_smmu_master_data *master;
	struct arm_smmu_strtab_ent *ste;

	if (!dev->iommu_fwspec)
		return -ENOENT;

	master = dev->iommu_fwspec->iommu_priv;
	smmu = master->smmu;
	ste = &master->ste;

	/* Already attached to a different domain? */
	if (ste->assigned)
		arm_smmu_detach_dev(dev);

	mutex_lock(&smmu_domain->init_mutex);

	if (!smmu_domain->smmu) {
		smmu_domain->smmu = smmu;
		ret = arm_smmu_domain_finalise(domain);
		if (ret) {
			smmu_domain->smmu = NULL;
			goto out_unlock;
		}
	} else if (smmu_domain->smmu != smmu) {
		dev_err(dev,
			"cannot attach to SMMU %s (upstream of %s)\n",
			dev_name(smmu_domain->smmu->dev),
			dev_name(smmu->dev));
		ret = -ENXIO;
		goto out_unlock;
	}

	ste->assigned = true;

	if (smmu_domain->stage == ARM_SMMU_DOMAIN_BYPASS) {
		ste->s1_cfg = NULL;
		ste->s2_cfg = NULL;
	} else if (smmu_domain->stage == ARM_SMMU_DOMAIN_S1) {
		ste->s1_cfg = &smmu_domain->s1_cfg;
		ste->s2_cfg = NULL;
		arm_smmu_write_ctx_desc(smmu, ste->s1_cfg);
	} else {
		ste->s1_cfg = NULL;
		ste->s2_cfg = &smmu_domain->s2_cfg;
	}

	arm_smmu_install_ste_for_dev(dev->iommu_fwspec);
out_unlock:
	mutex_unlock(&smmu_domain->init_mutex);
	return ret;
}