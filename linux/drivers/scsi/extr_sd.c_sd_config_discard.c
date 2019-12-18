#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scsi_disk {unsigned int unmap_alignment; unsigned int unmap_granularity; unsigned int provisioning_mode; unsigned int max_unmap_blocks; unsigned int max_ws_blocks; TYPE_3__* device; int /*<<< orphan*/  physical_block_size; TYPE_1__* disk; } ;
struct TYPE_5__ {unsigned int discard_alignment; int /*<<< orphan*/  discard_granularity; } ;
struct request_queue {TYPE_2__ limits; } ;
struct TYPE_6__ {unsigned int sector_size; int /*<<< orphan*/  unmap_limit_for_ws; } ;
struct TYPE_4__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
#define  SD_LBP_DISABLE 133 
#define  SD_LBP_FULL 132 
#define  SD_LBP_UNMAP 131 
#define  SD_LBP_WS10 130 
#define  SD_LBP_WS16 129 
#define  SD_LBP_ZERO 128 
 int /*<<< orphan*/  SD_MAX_WS10_BLOCKS ; 
 int /*<<< orphan*/  SD_MAX_WS16_BLOCKS ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min_not_zero (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_config_discard(struct scsi_disk *sdkp, unsigned int mode)
{
	struct request_queue *q = sdkp->disk->queue;
	unsigned int logical_block_size = sdkp->device->sector_size;
	unsigned int max_blocks = 0;

	q->limits.discard_alignment =
		sdkp->unmap_alignment * logical_block_size;
	q->limits.discard_granularity =
		max(sdkp->physical_block_size,
		    sdkp->unmap_granularity * logical_block_size);
	sdkp->provisioning_mode = mode;

	switch (mode) {

	case SD_LBP_FULL:
	case SD_LBP_DISABLE:
		blk_queue_max_discard_sectors(q, 0);
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		return;

	case SD_LBP_UNMAP:
		max_blocks = min_not_zero(sdkp->max_unmap_blocks,
					  (u32)SD_MAX_WS16_BLOCKS);
		break;

	case SD_LBP_WS16:
		if (sdkp->device->unmap_limit_for_ws)
			max_blocks = sdkp->max_unmap_blocks;
		else
			max_blocks = sdkp->max_ws_blocks;

		max_blocks = min_not_zero(max_blocks, (u32)SD_MAX_WS16_BLOCKS);
		break;

	case SD_LBP_WS10:
		if (sdkp->device->unmap_limit_for_ws)
			max_blocks = sdkp->max_unmap_blocks;
		else
			max_blocks = sdkp->max_ws_blocks;

		max_blocks = min_not_zero(max_blocks, (u32)SD_MAX_WS10_BLOCKS);
		break;

	case SD_LBP_ZERO:
		max_blocks = min_not_zero(sdkp->max_ws_blocks,
					  (u32)SD_MAX_WS10_BLOCKS);
		break;
	}

	blk_queue_max_discard_sectors(q, max_blocks * (logical_block_size >> 9));
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
}