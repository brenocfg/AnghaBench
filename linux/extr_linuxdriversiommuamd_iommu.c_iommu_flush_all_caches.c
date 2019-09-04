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
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_IA ; 
 int /*<<< orphan*/  amd_iommu_flush_all (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_flush_dte_all (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_flush_irt_all (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_flush_tlb_all (struct amd_iommu*) ; 
 scalar_t__ iommu_feature (struct amd_iommu*,int /*<<< orphan*/ ) ; 

void iommu_flush_all_caches(struct amd_iommu *iommu)
{
	if (iommu_feature(iommu, FEATURE_IA)) {
		amd_iommu_flush_all(iommu);
	} else {
		amd_iommu_flush_dte_all(iommu);
		amd_iommu_flush_irt_all(iommu);
		amd_iommu_flush_tlb_all(iommu);
	}
}