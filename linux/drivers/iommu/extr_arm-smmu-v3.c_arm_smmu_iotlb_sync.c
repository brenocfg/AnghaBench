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
struct iommu_iotlb_gather {int /*<<< orphan*/  pgsize; scalar_t__ start; scalar_t__ end; } ;
struct iommu_domain {int dummy; } ;
struct arm_smmu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_tlb_inv_range (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,struct arm_smmu_domain*) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void arm_smmu_iotlb_sync(struct iommu_domain *domain,
				struct iommu_iotlb_gather *gather)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	arm_smmu_tlb_inv_range(gather->start, gather->end - gather->start,
			       gather->pgsize, true, smmu_domain);
}