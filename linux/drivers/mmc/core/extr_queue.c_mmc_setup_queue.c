#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mmc_queue {int /*<<< orphan*/  wait; int /*<<< orphan*/  complete_lock; int /*<<< orphan*/  complete_work; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  queue; } ;
struct mmc_host {int max_req_size; int /*<<< orphan*/  max_seg_size; scalar_t__ can_dma_map_merge; int /*<<< orphan*/  max_blk_count; } ;
struct TYPE_5__ {unsigned int data_sector_size; } ;
struct mmc_card {TYPE_1__ ext_csd; struct mmc_host* host; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_can_use_dma_map_merging (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_blk_mq_complete_work ; 
 scalar_t__ mmc_can_erase (struct mmc_card*) ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 TYPE_2__* mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_get_max_segments (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_mq_recovery_handler ; 
 int /*<<< orphan*/  mmc_queue_setup_discard (int /*<<< orphan*/ ,struct mmc_card*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_max_segment_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mmc_setup_queue(struct mmc_queue *mq, struct mmc_card *card)
{
	struct mmc_host *host = card->host;
	unsigned block_size = 512;

	blk_queue_flag_set(QUEUE_FLAG_NONROT, mq->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, mq->queue);
	if (mmc_can_erase(card))
		mmc_queue_setup_discard(mq->queue, card);

	if (!mmc_dev(host)->dma_mask || !*mmc_dev(host)->dma_mask)
		blk_queue_bounce_limit(mq->queue, BLK_BOUNCE_HIGH);
	blk_queue_max_hw_sectors(mq->queue,
		min(host->max_blk_count, host->max_req_size / 512));
	if (host->can_dma_map_merge)
		WARN(!blk_queue_can_use_dma_map_merging(mq->queue,
							mmc_dev(host)),
		     "merging was advertised but not possible");
	blk_queue_max_segments(mq->queue, mmc_get_max_segments(host));

	if (mmc_card_mmc(card))
		block_size = card->ext_csd.data_sector_size;

	blk_queue_logical_block_size(mq->queue, block_size);
	/*
	 * After blk_queue_can_use_dma_map_merging() was called with succeed,
	 * since it calls blk_queue_virt_boundary(), the mmc should not call
	 * both blk_queue_max_segment_size().
	 */
	if (!host->can_dma_map_merge)
		blk_queue_max_segment_size(mq->queue,
			round_down(host->max_seg_size, block_size));

	dma_set_max_seg_size(mmc_dev(host), queue_max_segment_size(mq->queue));

	INIT_WORK(&mq->recovery_work, mmc_mq_recovery_handler);
	INIT_WORK(&mq->complete_work, mmc_blk_mq_complete_work);

	mutex_init(&mq->complete_lock);

	init_waitqueue_head(&mq->wait);
}