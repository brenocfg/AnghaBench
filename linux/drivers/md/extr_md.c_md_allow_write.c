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
struct mddev {int safemode; int /*<<< orphan*/  lock; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  sysfs_state; scalar_t__ safemode_delay; scalar_t__ in_sync; TYPE_1__* pers; scalar_t__ ro; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_SB_CHANGE_CLEAN ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void md_allow_write(struct mddev *mddev)
{
	if (!mddev->pers)
		return;
	if (mddev->ro)
		return;
	if (!mddev->pers->sync_request)
		return;

	spin_lock(&mddev->lock);
	if (mddev->in_sync) {
		mddev->in_sync = 0;
		set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
		set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
		if (mddev->safemode_delay &&
		    mddev->safemode == 0)
			mddev->safemode = 1;
		spin_unlock(&mddev->lock);
		md_update_sb(mddev, 0);
		sysfs_notify_dirent_safe(mddev->sysfs_state);
		/* wait for the dirty state to be recorded in the metadata */
		wait_event(mddev->sb_wait,
			   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));
	} else
		spin_unlock(&mddev->lock);
}