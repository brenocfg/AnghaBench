#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vsp1_dl_manager {int /*<<< orphan*/  lock; TYPE_1__* pending; TYPE_1__* queued; TYPE_1__* active; int /*<<< orphan*/  index; scalar_t__ singleshot; struct vsp1_device* vsp1; } ;
struct vsp1_device {int dummy; } ;
struct TYPE_3__ {unsigned int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_STATUS ; 
 int VI6_STATUS_FLD_STD (int /*<<< orphan*/ ) ; 
 unsigned int VSP1_DL_FRAME_END_COMPLETED ; 
 int VSP1_DL_FRAME_END_INTERNAL ; 
 unsigned int VSP1_DL_FRAME_END_WRITEBACK ; 
 int /*<<< orphan*/  __vsp1_dl_list_put (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dl_list_hw_enqueue (TYPE_1__*) ; 
 scalar_t__ vsp1_dl_list_hw_update_pending (struct vsp1_dl_manager*) ; 
 int vsp1_read (struct vsp1_device*,int /*<<< orphan*/ ) ; 

unsigned int vsp1_dlm_irq_frame_end(struct vsp1_dl_manager *dlm)
{
	struct vsp1_device *vsp1 = dlm->vsp1;
	u32 status = vsp1_read(vsp1, VI6_STATUS);
	unsigned int flags = 0;

	spin_lock(&dlm->lock);

	/*
	 * The mem-to-mem pipelines work in single-shot mode. No new display
	 * list can be queued, we don't have to do anything.
	 */
	if (dlm->singleshot) {
		__vsp1_dl_list_put(dlm->active);
		dlm->active = NULL;
		flags |= VSP1_DL_FRAME_END_COMPLETED;
		goto done;
	}

	/*
	 * If the commit operation raced with the interrupt and occurred after
	 * the frame end event but before interrupt processing, the hardware
	 * hasn't taken the update into account yet. We have to skip one frame
	 * and retry.
	 */
	if (vsp1_dl_list_hw_update_pending(dlm))
		goto done;

	/*
	 * Progressive streams report only TOP fields. If we have a BOTTOM
	 * field, we are interlaced, and expect the frame to complete on the
	 * next frame end interrupt.
	 */
	if (status & VI6_STATUS_FLD_STD(dlm->index))
		goto done;

	/*
	 * If the active display list has the writeback flag set, the frame
	 * completion marks the end of the writeback capture. Return the
	 * VSP1_DL_FRAME_END_WRITEBACK flag and reset the display list's
	 * writeback flag.
	 */
	if (dlm->active && (dlm->active->flags & VSP1_DL_FRAME_END_WRITEBACK)) {
		flags |= VSP1_DL_FRAME_END_WRITEBACK;
		dlm->active->flags &= ~VSP1_DL_FRAME_END_WRITEBACK;
	}

	/*
	 * The device starts processing the queued display list right after the
	 * frame end interrupt. The display list thus becomes active.
	 */
	if (dlm->queued) {
		if (dlm->queued->flags & VSP1_DL_FRAME_END_INTERNAL)
			flags |= VSP1_DL_FRAME_END_INTERNAL;
		dlm->queued->flags &= ~VSP1_DL_FRAME_END_INTERNAL;

		__vsp1_dl_list_put(dlm->active);
		dlm->active = dlm->queued;
		dlm->queued = NULL;
		flags |= VSP1_DL_FRAME_END_COMPLETED;
	}

	/*
	 * Now that the VSP has started processing the queued display list, we
	 * can queue the pending display list to the hardware if one has been
	 * prepared.
	 */
	if (dlm->pending) {
		vsp1_dl_list_hw_enqueue(dlm->pending);
		dlm->queued = dlm->pending;
		dlm->pending = NULL;
	}

done:
	spin_unlock(&dlm->lock);

	return flags;
}