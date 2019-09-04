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
typedef  enum iommu_cap { ____Placeholder_iommu_cap } iommu_cap ;

/* Variables and functions */
#define  IOMMU_CAP_CACHE_COHERENCY 129 
#define  IOMMU_CAP_NOEXEC 128 

__attribute__((used)) static bool qcom_iommu_capable(enum iommu_cap cap)
{
	switch (cap) {
	case IOMMU_CAP_CACHE_COHERENCY:
		/*
		 * Return true here as the SMMU can always send out coherent
		 * requests.
		 */
		return true;
	case IOMMU_CAP_NOEXEC:
		return true;
	default:
		return false;
	}
}