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
struct iommu_domain {int type; } ;
struct arm_smmu_domain {int non_strict; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  stage; int /*<<< orphan*/  smmu; } ;
typedef  enum iommu_attr { ____Placeholder_iommu_attr } iommu_attr ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_DOMAIN_NESTED ; 
 int /*<<< orphan*/  ARM_SMMU_DOMAIN_S1 ; 
#define  DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE 131 
#define  DOMAIN_ATTR_NESTING 130 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
#define  IOMMU_DOMAIN_DMA 129 
#define  IOMMU_DOMAIN_UNMANAGED 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int arm_smmu_domain_set_attr(struct iommu_domain *domain,
				    enum iommu_attr attr, void *data)
{
	int ret = 0;
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	mutex_lock(&smmu_domain->init_mutex);

	switch (domain->type) {
	case IOMMU_DOMAIN_UNMANAGED:
		switch (attr) {
		case DOMAIN_ATTR_NESTING:
			if (smmu_domain->smmu) {
				ret = -EPERM;
				goto out_unlock;
			}

			if (*(int *)data)
				smmu_domain->stage = ARM_SMMU_DOMAIN_NESTED;
			else
				smmu_domain->stage = ARM_SMMU_DOMAIN_S1;
			break;
		default:
			ret = -ENODEV;
		}
		break;
	case IOMMU_DOMAIN_DMA:
		switch(attr) {
		case DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE:
			smmu_domain->non_strict = *(int *)data;
			break;
		default:
			ret = -ENODEV;
		}
		break;
	default:
		ret = -EINVAL;
	}

out_unlock:
	mutex_unlock(&smmu_domain->init_mutex);
	return ret;
}