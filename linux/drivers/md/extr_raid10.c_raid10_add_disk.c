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
struct raid10_info {scalar_t__ recovery_disabled; TYPE_2__* rdev; scalar_t__ head_position; TYPE_2__* replacement; } ;
struct TYPE_3__ {int raid_disks; } ;
struct r10conf {int fullsync; struct raid10_info* mirrors; TYPE_1__ geo; } ;
struct mddev {scalar_t__ recovery_cp; scalar_t__ recovery_disabled; scalar_t__ queue; scalar_t__ gendisk; struct r10conf* private; } ;
struct md_rdev {int saved_raid_disk; int raid_disk; int data_offset; int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  In_sync ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  _enough (struct r10conf*,int,int) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_stack_limits (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ md_integrity_add_rdev (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  print_conf (struct r10conf*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid10_add_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r10conf *conf = mddev->private;
	int err = -EEXIST;
	int mirror;
	int first = 0;
	int last = conf->geo.raid_disks - 1;

	if (mddev->recovery_cp < MaxSector)
		/* only hot-add to in-sync arrays, as recovery is
		 * very different from resync
		 */
		return -EBUSY;
	if (rdev->saved_raid_disk < 0 && !_enough(conf, 1, -1))
		return -EINVAL;

	if (md_integrity_add_rdev(rdev, mddev))
		return -ENXIO;

	if (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	if (rdev->saved_raid_disk >= first &&
	    rdev->saved_raid_disk < conf->geo.raid_disks &&
	    conf->mirrors[rdev->saved_raid_disk].rdev == NULL)
		mirror = rdev->saved_raid_disk;
	else
		mirror = first;
	for ( ; mirror <= last ; mirror++) {
		struct raid10_info *p = &conf->mirrors[mirror];
		if (p->recovery_disabled == mddev->recovery_disabled)
			continue;
		if (p->rdev) {
			if (!test_bit(WantReplacement, &p->rdev->flags) ||
			    p->replacement != NULL)
				continue;
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = mirror;
			err = 0;
			if (mddev->gendisk)
				disk_stack_limits(mddev->gendisk, rdev->bdev,
						  rdev->data_offset << 9);
			conf->fullsync = 1;
			rcu_assign_pointer(p->replacement, rdev);
			break;
		}

		if (mddev->gendisk)
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);

		p->head_position = 0;
		p->recovery_disabled = mddev->recovery_disabled - 1;
		rdev->raid_disk = mirror;
		err = 0;
		if (rdev->saved_raid_disk != mirror)
			conf->fullsync = 1;
		rcu_assign_pointer(p->rdev, rdev);
		break;
	}
	if (mddev->queue && blk_queue_discard(bdev_get_queue(rdev->bdev)))
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);

	print_conf(conf);
	return err;
}