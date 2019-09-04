#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strip_zone {unsigned int dev_start; } ;
struct mddev {unsigned int chunk_sectors; scalar_t__ gendisk; int /*<<< orphan*/  private; int /*<<< orphan*/  bio_set; } ;
struct md_rdev {unsigned int data_offset; int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {unsigned int bi_sector; } ;
struct bio {int bi_opf; TYPE_2__* bi_disk; TYPE_1__ bi_iter; } ;
typedef  unsigned int sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 unsigned int bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* bio_split (struct bio*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_devt (scalar_t__) ; 
 struct strip_zone* find_zone (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct md_rdev* map_sector (struct mddev*,struct strip_zone*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  mddev_check_write_zeroes (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  mddev_check_writesame (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  raid0_handle_discard (struct mddev*,struct bio*) ; 
 unsigned int sector_div (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_block_bio_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool raid0_make_request(struct mddev *mddev, struct bio *bio)
{
	struct strip_zone *zone;
	struct md_rdev *tmp_dev;
	sector_t bio_sector;
	sector_t sector;
	unsigned chunk_sects;
	unsigned sectors;

	if (unlikely(bio->bi_opf & REQ_PREFLUSH)) {
		md_flush_request(mddev, bio);
		return true;
	}

	if (unlikely((bio_op(bio) == REQ_OP_DISCARD))) {
		raid0_handle_discard(mddev, bio);
		return true;
	}

	bio_sector = bio->bi_iter.bi_sector;
	sector = bio_sector;
	chunk_sects = mddev->chunk_sectors;

	sectors = chunk_sects -
		(likely(is_power_of_2(chunk_sects))
		 ? (sector & (chunk_sects-1))
		 : sector_div(sector, chunk_sects));

	/* Restore due to sector_div */
	sector = bio_sector;

	if (sectors < bio_sectors(bio)) {
		struct bio *split = bio_split(bio, sectors, GFP_NOIO,
					      &mddev->bio_set);
		bio_chain(split, bio);
		generic_make_request(bio);
		bio = split;
	}

	zone = find_zone(mddev->private, &sector);
	tmp_dev = map_sector(mddev, zone, sector, &sector);
	bio_set_dev(bio, tmp_dev->bdev);
	bio->bi_iter.bi_sector = sector + zone->dev_start +
		tmp_dev->data_offset;

	if (mddev->gendisk)
		trace_block_bio_remap(bio->bi_disk->queue, bio,
				disk_devt(mddev->gendisk), bio_sector);
	mddev_check_writesame(mddev, bio);
	mddev_check_write_zeroes(mddev, bio);
	generic_make_request(bio);
	return true;
}