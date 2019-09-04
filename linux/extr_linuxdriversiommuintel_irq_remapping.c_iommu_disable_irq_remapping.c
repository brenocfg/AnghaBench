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
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; int /*<<< orphan*/  gcmd; int /*<<< orphan*/  ecap; } ;

/* Variables and functions */
 scalar_t__ DMAR_GCMD_REG ; 
 scalar_t__ DMAR_GSTS_REG ; 
 int /*<<< orphan*/  DMA_GCMD_IRE ; 
 int DMA_GSTS_IRES ; 
 int /*<<< orphan*/  IOMMU_WAIT_OP (struct intel_iommu*,scalar_t__,int (*) (scalar_t__),int,int) ; 
 int /*<<< orphan*/  ecap_ir_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qi_global_iec (struct intel_iommu*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void iommu_disable_irq_remapping(struct intel_iommu *iommu)
{
	unsigned long flags;
	u32 sts;

	if (!ecap_ir_support(iommu->ecap))
		return;

	/*
	 * global invalidation of interrupt entry cache before disabling
	 * interrupt-remapping.
	 */
	qi_global_iec(iommu);

	raw_spin_lock_irqsave(&iommu->register_lock, flags);

	sts = readl(iommu->reg + DMAR_GSTS_REG);
	if (!(sts & DMA_GSTS_IRES))
		goto end;

	iommu->gcmd &= ~DMA_GCMD_IRE;
	writel(iommu->gcmd, iommu->reg + DMAR_GCMD_REG);

	IOMMU_WAIT_OP(iommu, DMAR_GSTS_REG,
		      readl, !(sts & DMA_GSTS_IRES), sts);

end:
	raw_spin_unlock_irqrestore(&iommu->register_lock, flags);
}