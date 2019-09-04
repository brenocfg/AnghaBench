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
typedef  int u64 ;
struct mmc_queue {int /*<<< orphan*/  wait; int /*<<< orphan*/  complete_lock; int /*<<< orphan*/  complete_work; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  queue; } ;
struct mmc_host {int max_req_size; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  max_segs; int /*<<< orphan*/  max_blk_count; } ;
struct mmc_card {struct mmc_host* host; } ;
struct TYPE_3__ {scalar_t__* dma_mask; } ;

/* Variables and functions */
 int BLK_BOUNCE_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_max_pfn (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_blk_mq_complete_work ; 
 scalar_t__ mmc_can_erase (struct mmc_card*) ; 
 TYPE_1__* mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_mq_recovery_handler ; 
 int /*<<< orphan*/  mmc_queue_setup_discard (int /*<<< orphan*/ ,struct mmc_card*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_setup_queue(struct mmc_queue *mq, struct mmc_card *card)
{
	struct mmc_host *host = card->host;
	u64 limit = BLK_BOUNCE_HIGH;

	if (mmc_dev(host)->dma_mask && *mmc_dev(host)->dma_mask)
		limit = (u64)dma_max_pfn(mmc_dev(host)) << PAGE_SHIFT;

	blk_queue_flag_set(QUEUE_FLAG_NONROT, mq->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, mq->queue);
	if (mmc_can_erase(card))
		mmc_queue_setup_discard(mq->queue, card);

	blk_queue_bounce_limit(mq->queue, limit);
	blk_queue_max_hw_sectors(mq->queue,
		min(host->max_blk_count, host->max_req_size / 512));
	blk_queue_max_segments(mq->queue, host->max_segs);
	blk_queue_max_segment_size(mq->queue, host->max_seg_size);

	INIT_WORK(&mq->recovery_work, mmc_mq_recovery_handler);
	INIT_WORK(&mq->complete_work, mmc_blk_mq_complete_work);

	mutex_init(&mq->complete_lock);

	init_waitqueue_head(&mq->wait);
}