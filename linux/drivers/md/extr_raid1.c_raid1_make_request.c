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
struct mddev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ READ ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  align_to_barrier_unit_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_write_start (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  raid1_read_request (struct mddev*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raid1_write_request (struct mddev*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool raid1_make_request(struct mddev *mddev, struct bio *bio)
{
	sector_t sectors;

	if (unlikely(bio->bi_opf & REQ_PREFLUSH)) {
		md_flush_request(mddev, bio);
		return true;
	}

	/*
	 * There is a limit to the maximum size, but
	 * the read/write handler might find a lower limit
	 * due to bad blocks.  To avoid multiple splits,
	 * we pass the maximum number of sectors down
	 * and let the lower level perform the split.
	 */
	sectors = align_to_barrier_unit_end(
		bio->bi_iter.bi_sector, bio_sectors(bio));

	if (bio_data_dir(bio) == READ)
		raid1_read_request(mddev, bio, sectors, NULL);
	else {
		if (!md_write_start(mddev,bio))
			return false;
		raid1_write_request(mddev, bio, sectors);
	}
	return true;
}