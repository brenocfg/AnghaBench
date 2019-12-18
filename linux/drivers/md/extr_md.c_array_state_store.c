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
struct mddev {int ro; scalar_t__ hold_active; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  gendisk; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  sb_flags; scalar_t__ pers; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; } ;
typedef  size_t ssize_t ;
typedef  enum array_state { ____Placeholder_array_state } array_state ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 scalar_t__ UNTIL_IOCTL ; 
#define  active 138 
#define  active_idle 137 
 int /*<<< orphan*/  array_states ; 
#define  bad_word 136 
#define  broken 135 
#define  clean 134 
#define  clear 133 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int do_md_run (struct mddev*) ; 
 int do_md_stop (struct mddev*,int,int /*<<< orphan*/ *) ; 
#define  inactive 132 
 int match_word (char const*,int /*<<< orphan*/ ) ; 
 int md_set_readonly (struct mddev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
#define  read_auto 131 
#define  readonly 130 
 int restart_array (struct mddev*) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_in_sync (struct mddev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
#define  suspended 129 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
#define  write_pending 128 

__attribute__((used)) static ssize_t
array_state_store(struct mddev *mddev, const char *buf, size_t len)
{
	int err = 0;
	enum array_state st = match_word(buf, array_states);

	if (mddev->pers && (st == active || st == clean) && mddev->ro != 1) {
		/* don't take reconfig_mutex when toggling between
		 * clean and active
		 */
		spin_lock(&mddev->lock);
		if (st == active) {
			restart_array(mddev);
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			md_wakeup_thread(mddev->thread);
			wake_up(&mddev->sb_wait);
		} else /* st == clean */ {
			restart_array(mddev);
			if (!set_in_sync(mddev))
				err = -EBUSY;
		}
		if (!err)
			sysfs_notify_dirent_safe(mddev->sysfs_state);
		spin_unlock(&mddev->lock);
		return err ?: len;
	}
	err = mddev_lock(mddev);
	if (err)
		return err;
	err = -EINVAL;
	switch(st) {
	case bad_word:
		break;
	case clear:
		/* stopping an active array */
		err = do_md_stop(mddev, 0, NULL);
		break;
	case inactive:
		/* stopping an active array */
		if (mddev->pers)
			err = do_md_stop(mddev, 2, NULL);
		else
			err = 0; /* already inactive */
		break;
	case suspended:
		break; /* not supported yet */
	case readonly:
		if (mddev->pers)
			err = md_set_readonly(mddev, NULL);
		else {
			mddev->ro = 1;
			set_disk_ro(mddev->gendisk, 1);
			err = do_md_run(mddev);
		}
		break;
	case read_auto:
		if (mddev->pers) {
			if (mddev->ro == 0)
				err = md_set_readonly(mddev, NULL);
			else if (mddev->ro == 1)
				err = restart_array(mddev);
			if (err == 0) {
				mddev->ro = 2;
				set_disk_ro(mddev->gendisk, 0);
			}
		} else {
			mddev->ro = 2;
			err = do_md_run(mddev);
		}
		break;
	case clean:
		if (mddev->pers) {
			err = restart_array(mddev);
			if (err)
				break;
			spin_lock(&mddev->lock);
			if (!set_in_sync(mddev))
				err = -EBUSY;
			spin_unlock(&mddev->lock);
		} else
			err = -EINVAL;
		break;
	case active:
		if (mddev->pers) {
			err = restart_array(mddev);
			if (err)
				break;
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			wake_up(&mddev->sb_wait);
			err = 0;
		} else {
			mddev->ro = 0;
			set_disk_ro(mddev->gendisk, 0);
			err = do_md_run(mddev);
		}
		break;
	case write_pending:
	case active_idle:
	case broken:
		/* these cannot be set */
		break;
	}

	if (!err) {
		if (mddev->hold_active == UNTIL_IOCTL)
			mddev->hold_active = 0;
		sysfs_notify_dirent_safe(mddev->sysfs_state);
	}
	mddev_unlock(mddev);
	return err ?: len;
}