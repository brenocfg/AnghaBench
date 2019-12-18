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
struct TYPE_5__ {int chunk_mask; scalar_t__ near_copies; scalar_t__ raid_disks; } ;
struct TYPE_4__ {int chunk_mask; scalar_t__ near_copies; scalar_t__ raid_disks; } ;
struct r10conf {int /*<<< orphan*/  wait_barrier; TYPE_2__ prev; TYPE_1__ geo; } ;
struct mddev {struct r10conf* private; } ;
struct TYPE_6__ {int bi_sector; } ;
struct bio {int bi_opf; TYPE_3__ bi_iter; } ;
typedef  int sector_t ;

/* Variables and functions */
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  __make_request (struct mddev*,struct bio*,int) ; 
 int bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_write_start (struct mddev*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool raid10_make_request(struct mddev *mddev, struct bio *bio)
{
	struct r10conf *conf = mddev->private;
	sector_t chunk_mask = (conf->geo.chunk_mask & conf->prev.chunk_mask);
	int chunk_sects = chunk_mask + 1;
	int sectors = bio_sectors(bio);

	if (unlikely(bio->bi_opf & REQ_PREFLUSH)) {
		md_flush_request(mddev, bio);
		return true;
	}

	if (!md_write_start(mddev, bio))
		return false;

	/*
	 * If this request crosses a chunk boundary, we need to split
	 * it.
	 */
	if (unlikely((bio->bi_iter.bi_sector & chunk_mask) +
		     sectors > chunk_sects
		     && (conf->geo.near_copies < conf->geo.raid_disks
			 || conf->prev.near_copies <
			 conf->prev.raid_disks)))
		sectors = chunk_sects -
			(bio->bi_iter.bi_sector &
			 (chunk_sects - 1));
	__make_request(mddev, bio, sectors);

	/* In case raid10d snuck in to freeze_array */
	wake_up(&conf->wait_barrier);
	return true;
}