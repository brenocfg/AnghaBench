#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  shadow_pdps; int /*<<< orphan*/  guest_pdps; } ;
struct intel_vgpu_mm {TYPE_4__* vgpu; TYPE_3__ ppgtt_mm; } ;
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* set_entry ) (int /*<<< orphan*/ ,struct intel_gvt_gtt_entry*,unsigned long,int,int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_8__ {TYPE_2__* gvt; } ;
struct TYPE_5__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_6__ {TYPE_1__ gtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct intel_gvt_gtt_entry*,unsigned long,int,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void _ppgtt_set_root_entry(struct intel_vgpu_mm *mm,
		struct intel_gvt_gtt_entry *entry, unsigned long index,
		bool guest)
{
	struct intel_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	pte_ops->set_entry(guest ? mm->ppgtt_mm.guest_pdps :
			   mm->ppgtt_mm.shadow_pdps,
			   entry, index, false, 0, mm->vgpu);
}