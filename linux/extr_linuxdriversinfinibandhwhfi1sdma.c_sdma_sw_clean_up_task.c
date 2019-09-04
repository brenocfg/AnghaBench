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
struct sdma_engine {int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  head_lock; scalar_t__* head_dma; int /*<<< orphan*/  desc_avail; scalar_t__ descq_head; scalar_t__ descq_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sdma_process_event (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_descq_freecnt (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_event_e40_sw_cleaned ; 
 int /*<<< orphan*/  sdma_flush (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_make_progress (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_sw_clean_up_task(unsigned long opaque)
{
	struct sdma_engine *sde = (struct sdma_engine *)opaque;
	unsigned long flags;

	spin_lock_irqsave(&sde->tail_lock, flags);
	write_seqlock(&sde->head_lock);

	/*
	 * At this point, the following should always be true:
	 * - We are halted, so no more descriptors are getting retired.
	 * - We are not running, so no one is submitting new work.
	 * - Only we can send the e40_sw_cleaned, so we can't start
	 *   running again until we say so.  So, the active list and
	 *   descq are ours to play with.
	 */

	/*
	 * In the error clean up sequence, software clean must be called
	 * before the hardware clean so we can use the hardware head in
	 * the progress routine.  A hardware clean or SPC unfreeze will
	 * reset the hardware head.
	 *
	 * Process all retired requests. The progress routine will use the
	 * latest physical hardware head - we are not running so speed does
	 * not matter.
	 */
	sdma_make_progress(sde, 0);

	sdma_flush(sde);

	/*
	 * Reset our notion of head and tail.
	 * Note that the HW registers have been reset via an earlier
	 * clean up.
	 */
	sde->descq_tail = 0;
	sde->descq_head = 0;
	sde->desc_avail = sdma_descq_freecnt(sde);
	*sde->head_dma = 0;

	__sdma_process_event(sde, sdma_event_e40_sw_cleaned);

	write_sequnlock(&sde->head_lock);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
}