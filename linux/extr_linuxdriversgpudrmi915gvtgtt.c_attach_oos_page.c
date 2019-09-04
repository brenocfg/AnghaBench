#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int gfn; int /*<<< orphan*/  type; struct intel_vgpu_oos_page* oos_page; } ;
struct intel_vgpu_ppgtt_spt {TYPE_2__ guest_page; TYPE_3__* vgpu; } ;
struct intel_vgpu_oos_page {int /*<<< orphan*/  id; int /*<<< orphan*/  list; struct intel_vgpu_ppgtt_spt* spt; int /*<<< orphan*/  mem; } ;
struct TYPE_4__ {int /*<<< orphan*/  oos_page_use_list_head; } ;
struct intel_gvt {TYPE_1__ gtt; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; struct intel_gvt* gvt; } ;

/* Variables and functions */
 int I915_GTT_PAGE_SHIFT ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int intel_gvt_hypervisor_read_gpa (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_oos_change (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_oos_page(struct intel_vgpu_oos_page *oos_page,
		struct intel_vgpu_ppgtt_spt *spt)
{
	struct intel_gvt *gvt = spt->vgpu->gvt;
	int ret;

	ret = intel_gvt_hypervisor_read_gpa(spt->vgpu,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			oos_page->mem, I915_GTT_PAGE_SIZE);
	if (ret)
		return ret;

	oos_page->spt = spt;
	spt->guest_page.oos_page = oos_page;

	list_move_tail(&oos_page->list, &gvt->gtt.oos_page_use_list_head);

	trace_oos_change(spt->vgpu->id, "attach", oos_page->id,
			 spt, spt->guest_page.type);
	return 0;
}