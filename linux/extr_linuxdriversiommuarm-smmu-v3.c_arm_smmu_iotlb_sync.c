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
struct arm_smmu_device {int dummy; } ;
struct TYPE_2__ {struct arm_smmu_device* smmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __arm_smmu_tlb_sync (struct arm_smmu_device*) ; 
 TYPE_1__* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void arm_smmu_iotlb_sync(struct iommu_domain *domain)
{
	struct arm_smmu_device *smmu = to_smmu_domain(domain)->smmu;

	if (smmu)
		__arm_smmu_tlb_sync(smmu);
}