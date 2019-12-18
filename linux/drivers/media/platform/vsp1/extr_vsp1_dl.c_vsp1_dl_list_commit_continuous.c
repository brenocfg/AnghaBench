#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vsp1_dl_manager {struct vsp1_dl_list* queued; struct vsp1_dl_list* pending; } ;
struct vsp1_dl_list {int flags; struct vsp1_dl_manager* dlm; } ;

/* Variables and functions */
 int VSP1_DL_FRAME_END_INTERNAL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vsp1_dl_list_put (struct vsp1_dl_list*) ; 
 int /*<<< orphan*/  vsp1_dl_list_hw_enqueue (struct vsp1_dl_list*) ; 
 scalar_t__ vsp1_dl_list_hw_update_pending (struct vsp1_dl_manager*) ; 

__attribute__((used)) static void vsp1_dl_list_commit_continuous(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * If a previous display list has been queued to the hardware but not
	 * processed yet, the VSP can start processing it at any time. In that
	 * case we can't replace the queued list by the new one, as we could
	 * race with the hardware. We thus mark the update as pending, it will
	 * be queued up to the hardware by the frame end interrupt handler.
	 *
	 * If a display list is already pending we simply drop it as the new
	 * display list is assumed to contain a more recent configuration. It is
	 * an error if the already pending list has the
	 * VSP1_DL_FRAME_END_INTERNAL flag set, as there is then a process
	 * waiting for that list to complete. This shouldn't happen as the
	 * waiting process should perform proper locking, but warn just in
	 * case.
	 */
	if (vsp1_dl_list_hw_update_pending(dlm)) {
		WARN_ON(dlm->pending &&
			(dlm->pending->flags & VSP1_DL_FRAME_END_INTERNAL));
		__vsp1_dl_list_put(dlm->pending);
		dlm->pending = dl;
		return;
	}

	/*
	 * Pass the new display list to the hardware and mark it as queued. It
	 * will become active when the hardware starts processing it.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	__vsp1_dl_list_put(dlm->queued);
	dlm->queued = dl;
}