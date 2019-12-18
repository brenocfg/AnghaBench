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
struct TYPE_5__ {int /*<<< orphan*/  gfn; int /*<<< orphan*/  type; struct intel_vgpu_oos_page* oos_page; } ;
struct intel_vgpu_ppgtt_spt {TYPE_2__ guest_page; TYPE_3__* vgpu; } ;
struct intel_vgpu_oos_page {int /*<<< orphan*/  vm_list; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  oos_page_list_head; } ;
struct TYPE_6__ {TYPE_1__ gtt; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN (int,char*) ; 
 int intel_vgpu_disable_page_track (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_oos_change (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppgtt_set_guest_page_oos(struct intel_vgpu_ppgtt_spt *spt)
{
	struct intel_vgpu_oos_page *oos_page = spt->guest_page.oos_page;

	if (WARN(!oos_page, "shadow PPGTT page should have a oos page\n"))
		return -EINVAL;

	trace_oos_change(spt->vgpu->id, "set page out of sync", oos_page->id,
			 spt, spt->guest_page.type);

	list_add_tail(&oos_page->vm_list, &spt->vgpu->gtt.oos_page_list_head);
	return intel_vgpu_disable_page_track(spt->vgpu, spt->guest_page.gfn);
}