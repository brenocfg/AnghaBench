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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int done_blit_handle; int cur_blit_handle; int cur; int /*<<< orphan*/  blit_lock; int /*<<< orphan*/ * blit_queue; } ;
typedef  TYPE_1__ drm_via_blitq_t ;

/* Variables and functions */
 int VIA_NUM_BLIT_SLOTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
via_dmablit_active(drm_via_blitq_t *blitq, int engine, uint32_t handle, wait_queue_head_t **queue)
{
	unsigned long irqsave;
	uint32_t slot;
	int active;

	spin_lock_irqsave(&blitq->blit_lock, irqsave);

	/*
	 * Allow for handle wraparounds.
	 */

	active = ((blitq->done_blit_handle - handle) > (1 << 23)) &&
		((blitq->cur_blit_handle - handle) <= (1 << 23));

	if (queue && active) {
		slot = handle - blitq->done_blit_handle + blitq->cur - 1;
		if (slot >= VIA_NUM_BLIT_SLOTS)
			slot -= VIA_NUM_BLIT_SLOTS;
		*queue = blitq->blit_queue + slot;
	}

	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

	return active;
}