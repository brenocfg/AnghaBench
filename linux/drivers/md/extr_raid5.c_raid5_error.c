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
struct r5conf {scalar_t__ max_degraded; scalar_t__ raid_disks; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  recovery_disabled; } ;
struct mddev {scalar_t__ degraded; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  recovery; int /*<<< orphan*/  recovery_disabled; struct r5conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Blocked ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  r5c_update_on_rdev_error (struct mddev*,struct md_rdev*) ; 
 scalar_t__ raid5_calc_degraded (struct r5conf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5_error(struct mddev *mddev, struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];
	struct r5conf *conf = mddev->private;
	unsigned long flags;
	pr_debug("raid456: error called\n");

	spin_lock_irqsave(&conf->device_lock, flags);

	if (test_bit(In_sync, &rdev->flags) &&
	    mddev->degraded == conf->max_degraded) {
		/*
		 * Don't allow to achieve failed state
		 * Don't try to recover this device
		 */
		conf->recovery_disabled = mddev->recovery_disabled;
		spin_unlock_irqrestore(&conf->device_lock, flags);
		return;
	}

	set_bit(Faulty, &rdev->flags);
	clear_bit(In_sync, &rdev->flags);
	mddev->degraded = raid5_calc_degraded(conf);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);

	set_bit(Blocked, &rdev->flags);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	pr_crit("md/raid:%s: Disk failure on %s, disabling device.\n"
		"md/raid:%s: Operation continuing on %d devices.\n",
		mdname(mddev),
		bdevname(rdev->bdev, b),
		mdname(mddev),
		conf->raid_disks - mddev->degraded);
	r5c_update_on_rdev_error(mddev, rdev);
}