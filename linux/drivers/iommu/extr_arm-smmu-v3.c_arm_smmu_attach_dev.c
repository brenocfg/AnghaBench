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
struct iommu_fwspec {struct arm_smmu_master* iommu_priv; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
struct arm_smmu_master {int /*<<< orphan*/  domain_head; int /*<<< orphan*/  ats_enabled; struct arm_smmu_domain* domain; struct arm_smmu_device* smmu; } ;
struct arm_smmu_domain {scalar_t__ stage; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  devices_lock; int /*<<< orphan*/  devices; int /*<<< orphan*/  s1_cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_DOMAIN_BYPASS ; 
 scalar_t__ ARM_SMMU_DOMAIN_S1 ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  arm_smmu_ats_supported (struct arm_smmu_master*) ; 
 int /*<<< orphan*/  arm_smmu_detach_dev (struct arm_smmu_master*) ; 
 int arm_smmu_domain_finalise (struct iommu_domain*) ; 
 int /*<<< orphan*/  arm_smmu_enable_ats (struct arm_smmu_master*) ; 
 int /*<<< orphan*/  arm_smmu_install_ste_for_dev (struct arm_smmu_master*) ; 
 int /*<<< orphan*/  arm_smmu_write_ctx_desc (struct arm_smmu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int arm_smmu_attach_dev(struct iommu_domain *domain, struct device *dev)
{
	int ret = 0;
	unsigned long flags;
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct arm_smmu_device *smmu;
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	struct arm_smmu_master *master;

	if (!fwspec)
		return -ENOENT;

	master = fwspec->iommu_priv;
	smmu = master->smmu;

	arm_smmu_detach_dev(master);

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

	master->domain = smmu_domain;

	if (smmu_domain->stage != ARM_SMMU_DOMAIN_BYPASS)
		master->ats_enabled = arm_smmu_ats_supported(master);

	if (smmu_domain->stage == ARM_SMMU_DOMAIN_S1)
		arm_smmu_write_ctx_desc(smmu, &smmu_domain->s1_cfg);

	arm_smmu_install_ste_for_dev(master);

	spin_lock_irqsave(&smmu_domain->devices_lock, flags);
	list_add(&master->domain_head, &smmu_domain->devices);
	spin_unlock_irqrestore(&smmu_domain->devices_lock, flags);

	arm_smmu_enable_ats(master);

out_unlock:
	mutex_unlock(&smmu_domain->init_mutex);
	return ret;
}