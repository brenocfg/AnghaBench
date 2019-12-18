#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  gfn; struct intel_vgpu_oos_page* oos_page; } ;
struct intel_vgpu_ppgtt_spt {TYPE_2__* vgpu; TYPE_1__ guest_page; } ;
struct intel_vgpu_oos_page {int /*<<< orphan*/  vm_list; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int intel_vgpu_enable_page_track (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int sync_oos_page (TYPE_2__*,struct intel_vgpu_oos_page*) ; 
 int /*<<< orphan*/  trace_oos_change (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppgtt_set_guest_page_sync(struct intel_vgpu_ppgtt_spt *spt)
{
	struct intel_vgpu_oos_page *oos_page = spt->guest_page.oos_page;
	int ret;

	ret = intel_vgpu_enable_page_track(spt->vgpu, spt->guest_page.gfn);
	if (ret)
		return ret;

	trace_oos_change(spt->vgpu->id, "set page sync", oos_page->id,
			 spt, spt->guest_page.type);

	list_del_init(&oos_page->vm_list);
	return sync_oos_page(spt->vgpu, oos_page);
}