#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_vgpu {TYPE_2__* gvt; } ;
struct intel_gvt_gtt_pte_ops {unsigned long (* get_pfn ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_3__ {unsigned long scratch_mfn; struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_4__ {TYPE_1__ gtt; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  intel_gvt_hypervisor_dma_unmap_guest_page (struct intel_vgpu*,unsigned long) ; 
 unsigned long stub1 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static void ggtt_invalidate_pte(struct intel_vgpu *vgpu,
		struct intel_gvt_gtt_entry *entry)
{
	struct intel_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	unsigned long pfn;

	pfn = pte_ops->get_pfn(entry);
	if (pfn != vgpu->gvt->gtt.scratch_mfn)
		intel_gvt_hypervisor_dma_unmap_guest_page(vgpu,
						pfn << PAGE_SHIFT);
}