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
typedef  int u64 ;
struct amd_iommu {int /*<<< orphan*/  flags; scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IOMMU_FLAG_TRANS_PRE_ENABLED ; 
 int CONTROL_IOMMU_EN ; 
 scalar_t__ MMIO_CONTROL_OFFSET ; 
 int readq (scalar_t__) ; 

__attribute__((used)) static void init_translation_status(struct amd_iommu *iommu)
{
	u64 ctrl;

	ctrl = readq(iommu->mmio_base + MMIO_CONTROL_OFFSET);
	if (ctrl & (1<<CONTROL_IOMMU_EN))
		iommu->flags |= AMD_IOMMU_FLAG_TRANS_PRE_ENABLED;
}