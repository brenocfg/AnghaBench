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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel_iommu {int /*<<< orphan*/  register_lock; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ DMAR_CCMD_REG ; 
#define  DMA_CCMD_DEVICE_INVL 130 
 int const DMA_CCMD_DID (int /*<<< orphan*/ ) ; 
#define  DMA_CCMD_DOMAIN_INVL 129 
 int const DMA_CCMD_FM (int /*<<< orphan*/ ) ; 
#define  DMA_CCMD_GLOBAL_INVL 128 
 int DMA_CCMD_ICC ; 
 int const DMA_CCMD_SID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_WAIT_OP (struct intel_iommu*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dmar_readq ; 
 int /*<<< orphan*/  dmar_writeq (scalar_t__,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __iommu_flush_context(struct intel_iommu *iommu,
				  u16 did, u16 source_id, u8 function_mask,
				  u64 type)
{
	u64 val = 0;
	unsigned long flag;

	switch (type) {
	case DMA_CCMD_GLOBAL_INVL:
		val = DMA_CCMD_GLOBAL_INVL;
		break;
	case DMA_CCMD_DOMAIN_INVL:
		val = DMA_CCMD_DOMAIN_INVL|DMA_CCMD_DID(did);
		break;
	case DMA_CCMD_DEVICE_INVL:
		val = DMA_CCMD_DEVICE_INVL|DMA_CCMD_DID(did)
			| DMA_CCMD_SID(source_id) | DMA_CCMD_FM(function_mask);
		break;
	default:
		BUG();
	}
	val |= DMA_CCMD_ICC;

	raw_spin_lock_irqsave(&iommu->register_lock, flag);
	dmar_writeq(iommu->reg + DMAR_CCMD_REG, val);

	/* Make sure hardware complete it */
	IOMMU_WAIT_OP(iommu, DMAR_CCMD_REG,
		dmar_readq, (!(val & DMA_CCMD_ICC)), val);

	raw_spin_unlock_irqrestore(&iommu->register_lock, flag);
}