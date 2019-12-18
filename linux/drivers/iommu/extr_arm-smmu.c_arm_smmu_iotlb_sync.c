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
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct arm_smmu_domain {TYPE_1__* flush_ops; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tlb_sync ) (struct arm_smmu_domain*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_rpm_get (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_rpm_put (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  stub1 (struct arm_smmu_domain*) ; 
 struct arm_smmu_domain* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static void arm_smmu_iotlb_sync(struct iommu_domain *domain,
				struct iommu_iotlb_gather *gather)
{
	struct arm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	struct arm_smmu_device *smmu = smmu_domain->smmu;

	if (smmu_domain->flush_ops) {
		arm_smmu_rpm_get(smmu);
		smmu_domain->flush_ops->tlb_sync(smmu_domain);
		arm_smmu_rpm_put(smmu);
	}
}