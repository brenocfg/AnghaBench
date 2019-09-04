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
struct intel_vgpu_execlist {TYPE_2__* pending_slot; TYPE_1__* running_context; TYPE_2__* running_slot; } ;
struct TYPE_4__ {int index; TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  context_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_dbg_el (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void switch_virtual_execlist_slot(struct intel_vgpu_execlist *execlist)
{
	gvt_dbg_el("[before] running slot %d/context %x pending slot %d\n",
			execlist->running_slot ?
			execlist->running_slot->index : -1,
			execlist->running_context ?
			execlist->running_context->context_id : 0,
			execlist->pending_slot ?
			execlist->pending_slot->index : -1);

	execlist->running_slot = execlist->pending_slot;
	execlist->pending_slot = NULL;
	execlist->running_context = execlist->running_context ?
		&execlist->running_slot->ctx[0] : NULL;

	gvt_dbg_el("[after] running slot %d/context %x pending slot %d\n",
			execlist->running_slot ?
			execlist->running_slot->index : -1,
			execlist->running_context ?
			execlist->running_context->context_id : 0,
			execlist->pending_slot ?
			execlist->pending_slot->index : -1);
}