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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_iotlb ) (struct intel_iommu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* flush_context ) (struct intel_iommu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct intel_iommu {TYPE_1__ flush; int /*<<< orphan*/  lock; } ;
struct context_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CCMD_DEVICE_INVL ; 
 int /*<<< orphan*/  DMA_CCMD_MASK_NOBIT ; 
 int /*<<< orphan*/  DMA_TLB_DSI_FLUSH ; 
 int /*<<< orphan*/  __iommu_flush_cache (struct intel_iommu*,struct context_entry*,int) ; 
 int /*<<< orphan*/  context_clear_entry (struct context_entry*) ; 
 int context_domain_id (struct context_entry*) ; 
 struct context_entry* iommu_context_addr (struct intel_iommu*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct intel_iommu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct intel_iommu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void domain_context_clear_one(struct intel_iommu *iommu, u8 bus, u8 devfn)
{
	unsigned long flags;
	struct context_entry *context;
	u16 did_old;

	if (!iommu)
		return;

	spin_lock_irqsave(&iommu->lock, flags);
	context = iommu_context_addr(iommu, bus, devfn, 0);
	if (!context) {
		spin_unlock_irqrestore(&iommu->lock, flags);
		return;
	}
	did_old = context_domain_id(context);
	context_clear_entry(context);
	__iommu_flush_cache(iommu, context, sizeof(*context));
	spin_unlock_irqrestore(&iommu->lock, flags);
	iommu->flush.flush_context(iommu,
				   did_old,
				   (((u16)bus) << 8) | devfn,
				   DMA_CCMD_MASK_NOBIT,
				   DMA_CCMD_DEVICE_INVL);
	iommu->flush.flush_iotlb(iommu,
				 did_old,
				 0,
				 0,
				 DMA_TLB_DSI_FLUSH);
}