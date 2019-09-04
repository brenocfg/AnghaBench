#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; } ;
struct intel_vgpu_ppgtt_spt {TYPE_5__ shadow_page; struct intel_vgpu* vgpu; } ;
struct TYPE_7__ {TYPE_1__* scratch_pt; } ;
struct intel_vgpu {TYPE_2__ gtt; TYPE_4__* gvt; } ;
struct intel_gvt_gtt_pte_ops {unsigned long (* get_pfn ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_8__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_9__ {TYPE_3__ gtt; } ;
struct TYPE_6__ {unsigned long page_mfn; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  intel_gvt_hypervisor_dma_unmap_guest_page (struct intel_vgpu*,unsigned long) ; 
 unsigned long stub1 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static inline void ppgtt_invalidate_pte(struct intel_vgpu_ppgtt_spt *spt,
		struct intel_gvt_gtt_entry *entry)
{
	struct intel_vgpu *vgpu = spt->vgpu;
	struct intel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	unsigned long pfn;
	int type;

	pfn = ops->get_pfn(entry);
	type = spt->shadow_page.type;

	/* Uninitialized spte or unshadowed spte. */
	if (!pfn || pfn == vgpu->gtt.scratch_pt[type].page_mfn)
		return;

	intel_gvt_hypervisor_dma_unmap_guest_page(vgpu, pfn << PAGE_SHIFT);
}