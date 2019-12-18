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
struct mddev {int ro; int /*<<< orphan*/  sysfs_action; scalar_t__ thread; int /*<<< orphan*/  recovery; scalar_t__ sync_thread; int /*<<< orphan*/  kobj; TYPE_1__* pers; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* start_reshape ) (struct mddev*) ;int /*<<< orphan*/  sync_request; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MD_RECOVERY_CHECK ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_match (char const*,char*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  md_reap_sync_thread (struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (scalar_t__) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct mddev*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
action_store(struct mddev *mddev, const char *page, size_t len)
{
	if (!mddev->pers || !mddev->pers->sync_request)
		return -EINVAL;


	if (cmd_match(page, "idle") || cmd_match(page, "frozen")) {
		if (cmd_match(page, "frozen"))
			set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		else
			clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) &&
		    mddev_lock(mddev) == 0) {
			flush_workqueue(md_misc_wq);
			if (mddev->sync_thread) {
				set_bit(MD_RECOVERY_INTR, &mddev->recovery);
				md_reap_sync_thread(mddev);
			}
			mddev_unlock(mddev);
		}
	} else if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		return -EBUSY;
	else if (cmd_match(page, "resync"))
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	else if (cmd_match(page, "recover")) {
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	} else if (cmd_match(page, "reshape")) {
		int err;
		if (mddev->pers->start_reshape == NULL)
			return -EINVAL;
		err = mddev_lock(mddev);
		if (!err) {
			if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
				err =  -EBUSY;
			else {
				clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
				err = mddev->pers->start_reshape(mddev);
			}
			mddev_unlock(mddev);
		}
		if (err)
			return err;
		sysfs_notify(&mddev->kobj, NULL, "degraded");
	} else {
		if (cmd_match(page, "check"))
			set_bit(MD_RECOVERY_CHECK, &mddev->recovery);
		else if (!cmd_match(page, "repair"))
			return -EINVAL;
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
		set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
	}
	if (mddev->ro == 2) {
		/* A write to sync_action is enough to justify
		 * canceling read-auto mode
		 */
		mddev->ro = 0;
		md_wakeup_thread(mddev->sync_thread);
	}
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thread(mddev->thread);
	sysfs_notify_dirent_safe(mddev->sysfs_action);
	return len;
}