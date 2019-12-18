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
struct stripe_head {int /*<<< orphan*/  state; } ;
struct r5conf {int quiesce; scalar_t__ max_degraded; int raid_disks; TYPE_1__* disks; scalar_t__ fullsync; int /*<<< orphan*/  wait_for_overlap; } ;
struct mddev {scalar_t__ dev_sectors; scalar_t__ curr_resync; scalar_t__ degraded; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  recovery; struct r5conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 struct md_rdev* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 int /*<<< orphan*/  end_reshape (struct r5conf*) ; 
 int /*<<< orphan*/  md_bitmap_close_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_cond_end_sync (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  md_bitmap_end_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  md_bitmap_start_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 struct stripe_head* raid5_get_active_stripe (struct r5conf*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ reshape_request (struct mddev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline sector_t raid5_sync_request(struct mddev *mddev, sector_t sector_nr,
					  int *skipped)
{
	struct r5conf *conf = mddev->private;
	struct stripe_head *sh;
	sector_t max_sector = mddev->dev_sectors;
	sector_t sync_blocks;
	int still_degraded = 0;
	int i;

	if (sector_nr >= max_sector) {
		/* just being told to finish up .. nothing much to do */

		if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)) {
			end_reshape(conf);
			return 0;
		}

		if (mddev->curr_resync < max_sector) /* aborted */
			md_bitmap_end_sync(mddev->bitmap, mddev->curr_resync,
					   &sync_blocks, 1);
		else /* completed sync */
			conf->fullsync = 0;
		md_bitmap_close_sync(mddev->bitmap);

		return 0;
	}

	/* Allow raid5_quiesce to complete */
	wait_event(conf->wait_for_overlap, conf->quiesce != 2);

	if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		return reshape_request(mddev, sector_nr, skipped);

	/* No need to check resync_max as we never do more than one
	 * stripe, and as resync_max will always be on a chunk boundary,
	 * if the check in md_do_sync didn't fire, there is no chance
	 * of overstepping resync_max here
	 */

	/* if there is too many failed drives and we are trying
	 * to resync, then assert that we are finished, because there is
	 * nothing we can do.
	 */
	if (mddev->degraded >= conf->max_degraded &&
	    test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) {
		sector_t rv = mddev->dev_sectors - sector_nr;
		*skipped = 1;
		return rv;
	}
	if (!test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    !conf->fullsync &&
	    !md_bitmap_start_sync(mddev->bitmap, sector_nr, &sync_blocks, 1) &&
	    sync_blocks >= STRIPE_SECTORS) {
		/* we can skip this block, and probably more */
		sync_blocks /= STRIPE_SECTORS;
		*skipped = 1;
		return sync_blocks * STRIPE_SECTORS; /* keep things rounded to whole stripes */
	}

	md_bitmap_cond_end_sync(mddev->bitmap, sector_nr, false);

	sh = raid5_get_active_stripe(conf, sector_nr, 0, 1, 0);
	if (sh == NULL) {
		sh = raid5_get_active_stripe(conf, sector_nr, 0, 0, 0);
		/* make sure we don't swamp the stripe cache if someone else
		 * is trying to get access
		 */
		schedule_timeout_uninterruptible(1);
	}
	/* Need to check if array will still be degraded after recovery/resync
	 * Note in case of > 1 drive failures it's possible we're rebuilding
	 * one drive while leaving another faulty drive in array.
	 */
	rcu_read_lock();
	for (i = 0; i < conf->raid_disks; i++) {
		struct md_rdev *rdev = READ_ONCE(conf->disks[i].rdev);

		if (rdev == NULL || test_bit(Faulty, &rdev->flags))
			still_degraded = 1;
	}
	rcu_read_unlock();

	md_bitmap_start_sync(mddev->bitmap, sector_nr, &sync_blocks, still_degraded);

	set_bit(STRIPE_SYNC_REQUESTED, &sh->state);
	set_bit(STRIPE_HANDLE, &sh->state);

	raid5_release_stripe(sh);

	return STRIPE_SECTORS;
}