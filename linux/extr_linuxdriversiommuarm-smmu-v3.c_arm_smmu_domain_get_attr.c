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
struct iommu_domain {scalar_t__ type; } ;
struct arm_smmu_domain {int /*<<< orphan*/  stage; } ;
typedef  enum iommu_attr { ____Placeholder_iommu_attr } iommu_attr ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_DOMAIN_NESTED ; 
#define  DOMAIN_ATTR_NESTING 128 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IOMMU_DOMAIN_UNMANAGED ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int arm_smmu_domain_get_attr(struct iommu_domain *domain,
				    enum iommu_attr attr, void *data)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	if (domain->type != IOMMU_DOMAIN_UNMANAGED)
		return -EINVAL;

	switch (attr) {
	case DOMAIN_ATTR_NESTING:
		*(int *)data = (smmu_domain->stage == ARM_SMMU_DOMAIN_NESTED);
		return 0;
	default:
		return -ENODEV;
	}
}