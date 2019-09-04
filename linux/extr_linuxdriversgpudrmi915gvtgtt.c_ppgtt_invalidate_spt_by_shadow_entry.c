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
struct intel_vgpu_ppgtt_spt {int dummy; } ;
struct TYPE_6__ {TYPE_1__* scratch_pt; } ;
struct intel_vgpu {TYPE_2__ gtt; TYPE_4__* gvt; } ;
struct intel_gvt_gtt_pte_ops {scalar_t__ (* get_pfn ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {scalar_t__ type; } ;
typedef  size_t intel_gvt_gtt_type_t ;
struct TYPE_7__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_8__ {TYPE_3__ gtt; } ;
struct TYPE_5__ {scalar_t__ page_mfn; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GTT_TYPE_PPGTT_ROOT_L3_ENTRY ; 
 scalar_t__ GTT_TYPE_PPGTT_ROOT_L4_ENTRY ; 
 size_t get_next_pt_type (scalar_t__) ; 
 int /*<<< orphan*/  gtt_type_is_pt (size_t) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,scalar_t__) ; 
 struct intel_vgpu_ppgtt_spt* intel_vgpu_find_spt_by_mfn (struct intel_vgpu*,scalar_t__) ; 
 int ppgtt_invalidate_spt (struct intel_vgpu_ppgtt_spt*) ; 
 scalar_t__ stub1 (struct intel_gvt_gtt_entry*) ; 
 scalar_t__ stub2 (struct intel_gvt_gtt_entry*) ; 
 scalar_t__ stub3 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static int ppgtt_invalidate_spt_by_shadow_entry(struct intel_vgpu *vgpu,
		struct intel_gvt_gtt_entry *e)
{
	struct intel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	struct intel_vgpu_ppgtt_spt *s;
	intel_gvt_gtt_type_t cur_pt_type;

	GEM_BUG_ON(!gtt_type_is_pt(get_next_pt_type(e->type)));

	if (e->type != GTT_TYPE_PPGTT_ROOT_L3_ENTRY
		&& e->type != GTT_TYPE_PPGTT_ROOT_L4_ENTRY) {
		cur_pt_type = get_next_pt_type(e->type) + 1;
		if (ops->get_pfn(e) ==
			vgpu->gtt.scratch_pt[cur_pt_type].page_mfn)
			return 0;
	}
	s = intel_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	if (!s) {
		gvt_vgpu_err("fail to find shadow page: mfn: 0x%lx\n",
				ops->get_pfn(e));
		return -ENXIO;
	}
	return ppgtt_invalidate_spt(s);
}