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
struct mddev {int /*<<< orphan*/  thread; int /*<<< orphan*/  sb_flags; } ;
struct md_rdev {struct mddev* mddev; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  kobj; int /*<<< orphan*/  flags; int /*<<< orphan*/  badblocks; scalar_t__ data_offset; scalar_t__ new_data_offset; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExternalBbl ; 
 int /*<<< orphan*/  MD_SB_CHANGE_CLEAN ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int badblocks_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rdev_set_badblocks(struct md_rdev *rdev, sector_t s, int sectors,
		       int is_new)
{
	struct mddev *mddev = rdev->mddev;
	int rv;
	if (is_new)
		s += rdev->new_data_offset;
	else
		s += rdev->data_offset;
	rv = badblocks_set(&rdev->badblocks, s, sectors, 0);
	if (rv == 0) {
		/* Make sure they get written out promptly */
		if (test_bit(ExternalBbl, &rdev->flags))
			sysfs_notify(&rdev->kobj, NULL,
				     "unacknowledged_bad_blocks");
		sysfs_notify_dirent_safe(rdev->sysfs_state);
		set_mask_bits(&mddev->sb_flags, 0,
			      BIT(MD_SB_CHANGE_CLEAN) | BIT(MD_SB_CHANGE_PENDING));
		md_wakeup_thread(rdev->mddev->thread);
		return 1;
	} else
		return 0;
}