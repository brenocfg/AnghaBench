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
struct arm_smmu_domain {int non_strict; int /*<<< orphan*/  stage; } ;
typedef  enum iommu_attr { ____Placeholder_iommu_attr } iommu_attr ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_DOMAIN_NESTED ; 
#define  DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE 131 
#define  DOMAIN_ATTR_NESTING 130 
 int EINVAL ; 
 int ENODEV ; 
#define  IOMMU_DOMAIN_DMA 129 
#define  IOMMU_DOMAIN_UNMANAGED 128 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int arm_smmu_domain_get_attr(struct iommu_domain *domain,
				    enum iommu_attr attr, void *data)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	switch(domain->type) {
	case IOMMU_DOMAIN_UNMANAGED:
		switch (attr) {
		case DOMAIN_ATTR_NESTING:
			*(int *)data = (smmu_domain->stage == ARM_SMMU_DOMAIN_NESTED);
			return 0;
		default:
			return -ENODEV;
		}
		break;
	case IOMMU_DOMAIN_DMA:
		switch (attr) {
		case DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE:
			*(int *)data = smmu_domain->non_strict;
			return 0;
		default:
			return -ENODEV;
		}
		break;
	default:
		return -EINVAL;
	}
}