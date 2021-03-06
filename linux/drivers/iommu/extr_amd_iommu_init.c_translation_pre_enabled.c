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
struct amd_iommu {int flags; } ;

/* Variables and functions */
 int AMD_IOMMU_FLAG_TRANS_PRE_ENABLED ; 

bool translation_pre_enabled(struct amd_iommu *iommu)
{
	return (iommu->flags & AMD_IOMMU_FLAG_TRANS_PRE_ENABLED);
}