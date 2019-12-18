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
struct TYPE_2__ {scalar_t__ raid_disks; } ;
struct r10conf {TYPE_1__ geo; int /*<<< orphan*/  device_lock; } ;
struct mddev {scalar_t__ degraded; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  recovery; int /*<<< orphan*/  fail_last_dev; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  raid_disk; } ;

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
 int /*<<< orphan*/  enough (struct r10conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid10_error(struct mddev *mddev, struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];
	struct r10conf *conf = mddev->private;
	unsigned long flags;

	/*
	 * If it is not operational, then we have already marked it as dead
	 * else if it is the last working disks with "fail_last_dev == false",
	 * ignore the error, let the next level up know.
	 * else mark the drive as failed
	 */
	spin_lock_irqsave(&conf->device_lock, flags);
	if (test_bit(In_sync, &rdev->flags) && !mddev->fail_last_dev
	    && !enough(conf, rdev->raid_disk)) {
		/*
		 * Don't fail the drive, just return an IO error.
		 */
		spin_unlock_irqrestore(&conf->device_lock, flags);
		return;
	}
	if (test_and_clear_bit(In_sync, &rdev->flags))
		mddev->degraded++;
	/*
	 * If recovery is running, make sure it aborts.
	 */
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_bit(Blocked, &rdev->flags);
	set_bit(Faulty, &rdev->flags);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	spin_unlock_irqrestore(&conf->device_lock, flags);
	pr_crit("md/raid10:%s: Disk failure on %s, disabling device.\n"
		"md/raid10:%s: Operation continuing on %d devices.\n",
		mdname(mddev), bdevname(rdev->bdev, b),
		mdname(mddev), conf->geo.raid_disks - mddev->degraded);
}