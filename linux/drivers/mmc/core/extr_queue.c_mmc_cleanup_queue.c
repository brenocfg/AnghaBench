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
struct request_queue {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/ * card; int /*<<< orphan*/  complete_work; int /*<<< orphan*/  tag_set; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 scalar_t__ blk_queue_quiesced (struct request_queue*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 

void mmc_cleanup_queue(struct mmc_queue *mq)
{
	struct request_queue *q = mq->queue;

	/*
	 * The legacy code handled the possibility of being suspended,
	 * so do that here too.
	 */
	if (blk_queue_quiesced(q))
		blk_mq_unquiesce_queue(q);

	blk_cleanup_queue(q);
	blk_mq_free_tag_set(&mq->tag_set);

	/*
	 * A request can be completed before the next request, potentially
	 * leaving a complete_work with nothing to do. Such a work item might
	 * still be queued at this point. Flush it.
	 */
	flush_work(&mq->complete_work);

	mq->card = NULL;
}