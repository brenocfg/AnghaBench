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
struct qib_pportdata {int /*<<< orphan*/  sdma_lock; scalar_t__ sdma_generation; scalar_t__* sdma_head_dma; scalar_t__ sdma_descq_head; scalar_t__ sdma_descq_tail; int /*<<< orphan*/  sdma_descq_added; int /*<<< orphan*/  sdma_descq_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sdma_activelist (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_event_e40_sw_cleaned ; 
 int /*<<< orphan*/  qib_sdma_make_progress (struct qib_pportdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdma_sw_clean_up_task(unsigned long opaque)
{
	struct qib_pportdata *ppd = (struct qib_pportdata *) opaque;
	unsigned long flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	/*
	 * At this point, the following should always be true:
	 * - We are halted, so no more descriptors are getting retired.
	 * - We are not running, so no one is submitting new work.
	 * - Only we can send the e40_sw_cleaned, so we can't start
	 *   running again until we say so.  So, the active list and
	 *   descq are ours to play with.
	 */

	/* Process all retired requests. */
	qib_sdma_make_progress(ppd);

	clear_sdma_activelist(ppd);

	/*
	 * Resync count of added and removed.  It is VERY important that
	 * sdma_descq_removed NEVER decrement - user_sdma depends on it.
	 */
	ppd->sdma_descq_removed = ppd->sdma_descq_added;

	/*
	 * Reset our notion of head and tail.
	 * Note that the HW registers will be reset when switching states
	 * due to calling __qib_sdma_process_event() below.
	 */
	ppd->sdma_descq_tail = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_head_dma[0] = 0;
	ppd->sdma_generation = 0;

	__qib_sdma_process_event(ppd, qib_sdma_event_e40_sw_cleaned);

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
}