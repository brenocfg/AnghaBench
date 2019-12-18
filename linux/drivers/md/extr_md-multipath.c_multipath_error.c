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
struct mpconf {int raid_disks; int /*<<< orphan*/  device_lock; } ;
struct mddev {int degraded; int /*<<< orphan*/  sb_flags; struct mpconf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multipath_error (struct mddev *mddev, struct md_rdev *rdev)
{
	struct mpconf *conf = mddev->private;
	char b[BDEVNAME_SIZE];

	if (conf->raid_disks - mddev->degraded <= 1) {
		/*
		 * Uh oh, we can do nothing if this is our last path, but
		 * first check if this is a queued request for a device
		 * which has just failed.
		 */
		pr_warn("multipath: only one IO path left and IO error.\n");
		/* leave it active... it's all we have */
		return;
	}
	/*
	 * Mark disk as unusable
	 */
	if (test_and_clear_bit(In_sync, &rdev->flags)) {
		unsigned long flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		mddev->degraded++;
		spin_unlock_irqrestore(&conf->device_lock, flags);
	}
	set_bit(Faulty, &rdev->flags);
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	pr_err("multipath: IO failure on %s, disabling IO path.\n"
	       "multipath: Operation continuing on %d IO paths.\n",
	       bdevname(rdev->bdev, b),
	       conf->raid_disks - mddev->degraded);
}