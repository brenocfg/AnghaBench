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
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 scalar_t__ DMAR_PMEN_REG ; 
 int DMA_PMEN_EPM ; 
 int DMA_PMEN_PRS ; 
 int /*<<< orphan*/  IOMMU_WAIT_OP (struct intel_iommu*,scalar_t__,int (*) (scalar_t__),int,int) ; 
 int /*<<< orphan*/  cap_phmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_plmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void iommu_disable_protect_mem_regions(struct intel_iommu *iommu)
{
	u32 pmen;
	unsigned long flags;

	if (!cap_plmr(iommu->cap) && !cap_phmr(iommu->cap))
		return;

	raw_spin_lock_irqsave(&iommu->register_lock, flags);
	pmen = readl(iommu->reg + DMAR_PMEN_REG);
	pmen &= ~DMA_PMEN_EPM;
	writel(pmen, iommu->reg + DMAR_PMEN_REG);

	/* wait for the protected region status bit to clear */
	IOMMU_WAIT_OP(iommu, DMAR_PMEN_REG,
		readl, !(pmen & DMA_PMEN_PRS), pmen);

	raw_spin_unlock_irqrestore(&iommu->register_lock, flags);
}