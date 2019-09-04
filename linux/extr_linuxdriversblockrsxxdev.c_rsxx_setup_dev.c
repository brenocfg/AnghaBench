#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_16__ {unsigned short block_size; } ;
struct TYPE_17__ {TYPE_1__ data; } ;
struct rsxx_cardinfo {scalar_t__ major; int disk_id; TYPE_4__* queue; TYPE_14__* gendisk; TYPE_2__ config; scalar_t__ config_valid; int /*<<< orphan*/  dev_lock; } ;
struct TYPE_18__ {int discard_granularity; int discard_alignment; } ;
struct TYPE_19__ {struct rsxx_cardinfo* queuedata; TYPE_3__ limits; } ;
struct TYPE_15__ {scalar_t__ major; TYPE_4__* queue; struct rsxx_cardinfo* private_data; int /*<<< orphan*/ * fops; scalar_t__ first_minor; int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int RSXX_HW_BLK_SIZE ; 
 TYPE_14__* alloc_disk (int /*<<< orphan*/ ) ; 
 TYPE_4__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (TYPE_4__*,int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_4__*,int) ; 
 int /*<<< orphan*/  blkdev_max_hw_sectors ; 
 int /*<<< orphan*/  blkdev_minors ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enable_blkdev ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ register_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsxx_discard_supported (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_fops ; 
 int /*<<< orphan*/  rsxx_make_request ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  unregister_blkdev (scalar_t__,int /*<<< orphan*/ ) ; 

int rsxx_setup_dev(struct rsxx_cardinfo *card)
{
	unsigned short blk_size;

	mutex_init(&card->dev_lock);

	if (!enable_blkdev)
		return 0;

	card->major = register_blkdev(0, DRIVER_NAME);
	if (card->major < 0) {
		dev_err(CARD_TO_DEV(card), "Failed to get major number\n");
		return -ENOMEM;
	}

	card->queue = blk_alloc_queue(GFP_KERNEL);
	if (!card->queue) {
		dev_err(CARD_TO_DEV(card), "Failed queue alloc\n");
		unregister_blkdev(card->major, DRIVER_NAME);
		return -ENOMEM;
	}

	card->gendisk = alloc_disk(blkdev_minors);
	if (!card->gendisk) {
		dev_err(CARD_TO_DEV(card), "Failed disk alloc\n");
		blk_cleanup_queue(card->queue);
		unregister_blkdev(card->major, DRIVER_NAME);
		return -ENOMEM;
	}

	if (card->config_valid) {
		blk_size = card->config.data.block_size;
		blk_queue_dma_alignment(card->queue, blk_size - 1);
		blk_queue_logical_block_size(card->queue, blk_size);
	}

	blk_queue_make_request(card->queue, rsxx_make_request);
	blk_queue_max_hw_sectors(card->queue, blkdev_max_hw_sectors);
	blk_queue_physical_block_size(card->queue, RSXX_HW_BLK_SIZE);

	blk_queue_flag_set(QUEUE_FLAG_NONROT, card->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, card->queue);
	if (rsxx_discard_supported(card)) {
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, card->queue);
		blk_queue_max_discard_sectors(card->queue,
						RSXX_HW_BLK_SIZE >> 9);
		card->queue->limits.discard_granularity = RSXX_HW_BLK_SIZE;
		card->queue->limits.discard_alignment   = RSXX_HW_BLK_SIZE;
	}

	card->queue->queuedata = card;

	snprintf(card->gendisk->disk_name, sizeof(card->gendisk->disk_name),
		 "rsxx%d", card->disk_id);
	card->gendisk->major = card->major;
	card->gendisk->first_minor = 0;
	card->gendisk->fops = &rsxx_fops;
	card->gendisk->private_data = card;
	card->gendisk->queue = card->queue;

	return 0;
}