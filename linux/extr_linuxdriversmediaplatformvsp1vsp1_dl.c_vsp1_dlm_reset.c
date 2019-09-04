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
struct vsp1_dl_manager {int /*<<< orphan*/ * pending; int /*<<< orphan*/ * queued; int /*<<< orphan*/ * active; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vsp1_dl_list_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vsp1_dlm_reset(struct vsp1_dl_manager *dlm)
{
	unsigned long flags;

	spin_lock_irqsave(&dlm->lock, flags);

	__vsp1_dl_list_put(dlm->active);
	__vsp1_dl_list_put(dlm->queued);
	__vsp1_dl_list_put(dlm->pending);

	spin_unlock_irqrestore(&dlm->lock, flags);

	dlm->active = NULL;
	dlm->queued = NULL;
	dlm->pending = NULL;
}