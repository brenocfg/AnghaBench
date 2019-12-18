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
struct TYPE_2__ {int shadowed; int /*<<< orphan*/  shadow_pdps; } ;
struct intel_vgpu_mm {TYPE_1__ ppgtt_mm; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  id; struct intel_gvt* gvt; } ;
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* test_present ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {scalar_t__ val64; int /*<<< orphan*/  type; } ;
struct intel_gvt_gtt {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct intel_gvt {struct intel_gvt_gtt gtt; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_get_shadow_root_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  ppgtt_invalidate_spt_by_shadow_entry (struct intel_vgpu*,struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  ppgtt_set_shadow_root_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  trace_spt_guest_change (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void invalidate_ppgtt_mm(struct intel_vgpu_mm *mm)
{
	struct intel_vgpu *vgpu = mm->vgpu;
	struct intel_gvt *gvt = vgpu->gvt;
	struct intel_gvt_gtt *gtt = &gvt->gtt;
	struct intel_gvt_gtt_pte_ops *ops = gtt->pte_ops;
	struct intel_gvt_gtt_entry se;
	int index;

	if (!mm->ppgtt_mm.shadowed)
		return;

	for (index = 0; index < ARRAY_SIZE(mm->ppgtt_mm.shadow_pdps); index++) {
		ppgtt_get_shadow_root_entry(mm, &se, index);

		if (!ops->test_present(&se))
			continue;

		ppgtt_invalidate_spt_by_shadow_entry(vgpu, &se);
		se.val64 = 0;
		ppgtt_set_shadow_root_entry(mm, &se, index);

		trace_spt_guest_change(vgpu->id, "destroy root pointer",
				       NULL, se.type, se.val64, index);
	}

	mm->ppgtt_mm.shadowed = false;
}