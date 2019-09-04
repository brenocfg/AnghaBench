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
struct mddev {int ro; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; int /*<<< orphan*/  gendisk; scalar_t__ pers; TYPE_1__* sync_thread; int /*<<< orphan*/  openers; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_wait; scalar_t__ external; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsk; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  __md_stop_writes (struct mddev*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_lock_nointr (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resync_wait ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int md_set_readonly(struct mddev *mddev, struct block_device *bdev)
{
	int err = 0;
	int did_freeze = 0;

	if (!test_bit(MD_RECOVERY_FROZEN, &mddev->recovery)) {
		did_freeze = 1;
		set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		md_wakeup_thread(mddev->thread);
	}
	if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	if (mddev->sync_thread)
		/* Thread might be blocked waiting for metadata update
		 * which will now never happen */
		wake_up_process(mddev->sync_thread->tsk);

	if (mddev->external && test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags))
		return -EBUSY;
	mddev_unlock(mddev);
	wait_event(resync_wait, !test_bit(MD_RECOVERY_RUNNING,
					  &mddev->recovery));
	wait_event(mddev->sb_wait,
		   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));
	mddev_lock_nointr(mddev);

	mutex_lock(&mddev->open_mutex);
	if ((mddev->pers && atomic_read(&mddev->openers) > !!bdev) ||
	    mddev->sync_thread ||
	    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery)) {
		pr_warn("md: %s still in use.\n",mdname(mddev));
		if (did_freeze) {
			clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			md_wakeup_thread(mddev->thread);
		}
		err = -EBUSY;
		goto out;
	}
	if (mddev->pers) {
		__md_stop_writes(mddev);

		err  = -ENXIO;
		if (mddev->ro==1)
			goto out;
		mddev->ro = 1;
		set_disk_ro(mddev->gendisk, 1);
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thread(mddev->thread);
		sysfs_notify_dirent_safe(mddev->sysfs_state);
		err = 0;
	}
out:
	mutex_unlock(&mddev->open_mutex);
	return err;
}