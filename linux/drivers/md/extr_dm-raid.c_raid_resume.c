#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mddev {scalar_t__ delta_disks; scalar_t__ in_sync; scalar_t__ ro; int /*<<< orphan*/  recovery; } ;
struct raid_set {int /*<<< orphan*/  runtime_flags; struct mddev md; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  RT_FLAG_RS_RESUMED ; 
 int /*<<< orphan*/  RT_FLAG_RS_SUSPENDED ; 
 int /*<<< orphan*/  attempt_restore_of_faulty_devices (struct raid_set*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mddev_lock_nointr (struct mddev*) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  rs_set_capacity (struct raid_set*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_resume(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;
	struct mddev *mddev = &rs->md;

	if (test_and_set_bit(RT_FLAG_RS_RESUMED, &rs->runtime_flags)) {
		/*
		 * A secondary resume while the device is active.
		 * Take this opportunity to check whether any failed
		 * devices are reachable again.
		 */
		attempt_restore_of_faulty_devices(rs);
	}

	if (test_and_clear_bit(RT_FLAG_RS_SUSPENDED, &rs->runtime_flags)) {
		/* Only reduce raid set size before running a disk removing reshape. */
		if (mddev->delta_disks < 0)
			rs_set_capacity(rs);

		mddev_lock_nointr(mddev);
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		mddev->ro = 0;
		mddev->in_sync = 0;
		mddev_resume(mddev);
		mddev_unlock(mddev);
	}
}