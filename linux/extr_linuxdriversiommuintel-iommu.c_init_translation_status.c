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
typedef  int u32 ;
struct intel_iommu {int /*<<< orphan*/  flags; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DMAR_GSTS_REG ; 
 int DMA_GSTS_TES ; 
 int /*<<< orphan*/  VTD_FLAG_TRANS_PRE_ENABLED ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void init_translation_status(struct intel_iommu *iommu)
{
	u32 gsts;

	gsts = readl(iommu->reg + DMAR_GSTS_REG);
	if (gsts & DMA_GSTS_TES)
		iommu->flags |= VTD_FLAG_TRANS_PRE_ENABLED;
}