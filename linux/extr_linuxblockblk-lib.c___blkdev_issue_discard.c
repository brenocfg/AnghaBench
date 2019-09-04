#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {int bi_sector; unsigned int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BLKDEV_DISCARD_SECURE ; 
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 unsigned int REQ_OP_DISCARD ; 
 unsigned int REQ_OP_SECURE_ERASE ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 scalar_t__ bdev_read_only (struct block_device*) ; 
 int /*<<< orphan*/  bio_allowed_max_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_secure_erase (struct request_queue*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 struct bio* next_bio (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio_wait (struct bio*) ; 

int __blkdev_issue_discard(struct block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, int flags,
		struct bio **biop)
{
	struct request_queue *q = bdev_get_queue(bdev);
	struct bio *bio = *biop;
	unsigned int op;
	sector_t bs_mask;

	if (!q)
		return -ENXIO;

	if (bdev_read_only(bdev))
		return -EPERM;

	if (flags & BLKDEV_DISCARD_SECURE) {
		if (!blk_queue_secure_erase(q))
			return -EOPNOTSUPP;
		op = REQ_OP_SECURE_ERASE;
	} else {
		if (!blk_queue_discard(q))
			return -EOPNOTSUPP;
		op = REQ_OP_DISCARD;
	}

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	if ((sector | nr_sects) & bs_mask)
		return -EINVAL;

	while (nr_sects) {
		unsigned int req_sects = nr_sects;
		sector_t end_sect;

		if (!req_sects)
			goto fail;
		req_sects = min(req_sects, bio_allowed_max_sectors(q));

		end_sect = sector + req_sects;

		bio = next_bio(bio, 0, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio_set_op_attrs(bio, op, 0);

		bio->bi_iter.bi_size = req_sects << 9;
		nr_sects -= req_sects;
		sector = end_sect;

		/*
		 * We can loop for a long time in here, if someone does
		 * full device discards (like mkfs). Be nice and allow
		 * us to schedule out to avoid softlocking if preempt
		 * is disabled.
		 */
		cond_resched();
	}

	*biop = bio;
	return 0;

fail:
	if (bio) {
		submit_bio_wait(bio);
		bio_put(bio);
	}
	*biop = NULL;
	return -EOPNOTSUPP;
}