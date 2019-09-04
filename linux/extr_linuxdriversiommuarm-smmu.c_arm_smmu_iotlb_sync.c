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
struct arm_smmu_domain {TYPE_1__* tlb_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tlb_sync ) (struct arm_smmu_domain*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct arm_smmu_domain*) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void arm_smmu_iotlb_sync(struct iommu_domain *domain)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	if (smmu_domain->tlb_ops)
		smmu_domain->tlb_ops->tlb_sync(smmu_domain);
}