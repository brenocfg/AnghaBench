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
struct request_queue {int dummy; } ;
struct raid_set {int raid_disks; TYPE_1__* dev; struct dm_target* ti; } ;
struct dm_target {int num_discard_bios; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {TYPE_2__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 int /*<<< orphan*/  devices_handle_discard_safely ; 
 int rs_is_raid456 (struct raid_set*) ; 

__attribute__((used)) static void configure_discard_support(struct raid_set *rs)
{
	int i;
	bool raid456;
	struct dm_target *ti = rs->ti;

	/*
	 * XXX: RAID level 4,5,6 require zeroing for safety.
	 */
	raid456 = rs_is_raid456(rs);

	for (i = 0; i < rs->raid_disks; i++) {
		struct request_queue *q;

		if (!rs->dev[i].rdev.bdev)
			continue;

		q = bdev_get_queue(rs->dev[i].rdev.bdev);
		if (!q || !blk_queue_discard(q))
			return;

		if (raid456) {
			if (!devices_handle_discard_safely) {
				DMERR("raid456 discard support disabled due to discard_zeroes_data uncertainty.");
				DMERR("Set dm-raid.devices_handle_discard_safely=Y to override.");
				return;
			}
		}
	}

	ti->num_discard_bios = 1;
}