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
struct mddev {scalar_t__ gendisk; int /*<<< orphan*/  bio_set; } ;
struct dev_info {scalar_t__ end_sector; TYPE_3__* rdev; } ;
struct TYPE_5__ {scalar_t__ bi_sector; } ;
struct bio {int bi_opf; TYPE_2__ bi_iter; TYPE_1__* bi_disk; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {scalar_t__ sectors; scalar_t__ data_offset; int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* bio_split (struct bio*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (scalar_t__) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int is_mddev_broken (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  mddev_check_write_zeroes (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  mddev_check_writesame (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_block_bio_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 struct dev_info* which_dev (struct mddev*,scalar_t__) ; 

__attribute__((used)) static bool linear_make_request(struct mddev *mddev, struct bio *bio)
{
	char b[BDEVNAME_SIZE];
	struct dev_info *tmp_dev;
	sector_t start_sector, end_sector, data_offset;
	sector_t bio_sector = bio->bi_iter.bi_sector;

	if (unlikely(bio->bi_opf & REQ_PREFLUSH)) {
		md_flush_request(mddev, bio);
		return true;
	}

	tmp_dev = which_dev(mddev, bio_sector);
	start_sector = tmp_dev->end_sector - tmp_dev->rdev->sectors;
	end_sector = tmp_dev->end_sector;
	data_offset = tmp_dev->rdev->data_offset;

	if (unlikely(bio_sector >= end_sector ||
		     bio_sector < start_sector))
		goto out_of_bounds;

	if (unlikely(is_mddev_broken(tmp_dev->rdev, "linear"))) {
		bio_io_error(bio);
		return true;
	}

	if (unlikely(bio_end_sector(bio) > end_sector)) {
		/* This bio crosses a device boundary, so we have to split it */
		struct bio *split = bio_split(bio, end_sector - bio_sector,
					      GFP_NOIO, &mddev->bio_set);
		bio_chain(split, bio);
		generic_make_request(bio);
		bio = split;
	}

	bio_set_dev(bio, tmp_dev->rdev->bdev);
	bio->bi_iter.bi_sector = bio->bi_iter.bi_sector -
		start_sector + data_offset;

	if (unlikely((bio_op(bio) == REQ_OP_DISCARD) &&
		     !blk_queue_discard(bio->bi_disk->queue))) {
		/* Just ignore it */
		bio_endio(bio);
	} else {
		if (mddev->gendisk)
			trace_block_bio_remap(bio->bi_disk->queue,
					      bio, disk_devt(mddev->gendisk),
					      bio_sector);
		mddev_check_writesame(mddev, bio);
		mddev_check_write_zeroes(mddev, bio);
		generic_make_request(bio);
	}
	return true;

out_of_bounds:
	pr_err("md/linear:%s: make_request: Sector %llu out of bounds on dev %s: %llu sectors, offset %llu\n",
	       mdname(mddev),
	       (unsigned long long)bio->bi_iter.bi_sector,
	       bdevname(tmp_dev->rdev->bdev, b),
	       (unsigned long long)tmp_dev->rdev->sectors,
	       (unsigned long long)start_sector);
	bio_io_error(bio);
	return true;
}