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
struct r1conf {int raid_disks; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  recovery_disabled; } ;
struct mddev {int degraded; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  recovery; int /*<<< orphan*/  recovery_disabled; int /*<<< orphan*/  fail_last_dev; struct r1conf* private; } ;
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
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid1_error(struct mddev *mddev, struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];
	struct r1conf *conf = mddev->private;
	unsigned long flags;

	/*
	 * If it is not operational, then we have already marked it as dead
	 * else if it is the last working disks with "fail_last_dev == false",
	 * ignore the error, let the next level up know.
	 * else mark the drive as failed
	 */
	spin_lock_irqsave(&conf->device_lock, flags);
	if (test_bit(In_sync, &rdev->flags) && !mddev->fail_last_dev
	    && (conf->raid_disks - mddev->degraded) == 1) {
		/*
		 * Don't fail the drive, act as though we were just a
		 * normal single drive.
		 * However don't try a recovery from this drive as
		 * it is very likely to fail.
		 */
		conf->recovery_disabled = mddev->recovery_disabled;
		spin_unlock_irqrestore(&conf->device_lock, flags);
		return;
	}
	set_bit(Blocked, &rdev->flags);
	if (test_and_clear_bit(In_sync, &rdev->flags))
		mddev->degraded++;
	set_bit(Faulty, &rdev->flags);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	/*
	 * if recovery is running, make sure it aborts.
	 */
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	pr_crit("md/raid1:%s: Disk failure on %s, disabling device.\n"
		"md/raid1:%s: Operation continuing on %d devices.\n",
		mdname(mddev), bdevname(rdev->bdev, b),
		mdname(mddev), conf->raid_disks - mddev->degraded);
}