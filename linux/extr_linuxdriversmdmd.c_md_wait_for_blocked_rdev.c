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
struct mddev {int dummy; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  blocked_wait; int /*<<< orphan*/  sysfs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Blocked ; 
 int /*<<< orphan*/  BlockedBadBlocks ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void md_wait_for_blocked_rdev(struct md_rdev *rdev, struct mddev *mddev)
{
	sysfs_notify_dirent_safe(rdev->sysfs_state);
	wait_event_timeout(rdev->blocked_wait,
			   !test_bit(Blocked, &rdev->flags) &&
			   !test_bit(BlockedBadBlocks, &rdev->flags),
			   msecs_to_jiffies(5000));
	rdev_dec_pending(rdev, mddev);
}