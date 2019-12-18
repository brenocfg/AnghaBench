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
typedef  int /*<<< orphan*/  u8 ;
struct amd_iommu {int /*<<< orphan*/  max_counters; } ;

/* Variables and functions */
 struct amd_iommu* get_amd_iommu (unsigned int) ; 

u8 amd_iommu_pc_get_max_counters(unsigned int idx)
{
	struct amd_iommu *iommu = get_amd_iommu(idx);

	if (iommu)
		return iommu->max_counters;

	return 0;
}