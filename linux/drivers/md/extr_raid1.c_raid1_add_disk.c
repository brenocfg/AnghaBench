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
struct raid1_info {TYPE_1__* rdev; scalar_t__ head_position; } ;
struct r1conf {int raid_disks; scalar_t__ recovery_disabled; int fullsync; struct raid1_info* mirrors; } ;
struct mddev {scalar_t__ recovery_disabled; scalar_t__ queue; scalar_t__ gendisk; struct r1conf* private; } ;
struct md_rdev {int raid_disk; int saved_raid_disk; int data_offset; int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int ENXIO ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_stack_limits (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ md_integrity_add_rdev (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  print_conf (struct r1conf*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (TYPE_1__*,struct md_rdev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid1_add_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r1conf *conf = mddev->private;
	int err = -EEXIST;
	int mirror = 0;
	struct raid1_info *p;
	int first = 0;
	int last = conf->raid_disks - 1;

	if (mddev->recovery_disabled == conf->recovery_disabled)
		return -EBUSY;

	if (md_integrity_add_rdev(rdev, mddev))
		return -ENXIO;

	if (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	/*
	 * find the disk ... but prefer rdev->saved_raid_disk
	 * if possible.
	 */
	if (rdev->saved_raid_disk >= 0 &&
	    rdev->saved_raid_disk >= first &&
	    rdev->saved_raid_disk < conf->raid_disks &&
	    conf->mirrors[rdev->saved_raid_disk].rdev == NULL)
		first = last = rdev->saved_raid_disk;

	for (mirror = first; mirror <= last; mirror++) {
		p = conf->mirrors + mirror;
		if (!p->rdev) {
			if (mddev->gendisk)
				disk_stack_limits(mddev->gendisk, rdev->bdev,
						  rdev->data_offset << 9);

			p->head_position = 0;
			rdev->raid_disk = mirror;
			err = 0;
			/* As all devices are equivalent, we don't need a full recovery
			 * if this was recently any drive of the array
			 */
			if (rdev->saved_raid_disk < 0)
				conf->fullsync = 1;
			rcu_assign_pointer(p->rdev, rdev);
			break;
		}
		if (test_bit(WantReplacement, &p->rdev->flags) &&
		    p[conf->raid_disks].rdev == NULL) {
			/* Add this device as a replacement */
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = mirror;
			err = 0;
			conf->fullsync = 1;
			rcu_assign_pointer(p[conf->raid_disks].rdev, rdev);
			break;
		}
	}
	if (mddev->queue && blk_queue_discard(bdev_get_queue(rdev->bdev)))
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);
	print_conf(conf);
	return err;
}