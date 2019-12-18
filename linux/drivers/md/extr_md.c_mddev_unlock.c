#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sd; } ;
struct mddev {int sysfs_active; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  thread; int /*<<< orphan*/  reconfig_mutex; int /*<<< orphan*/ * sysfs_action; TYPE_2__ kobj; TYPE_1__* pers; struct attribute_group* to_remove; } ;
struct attribute_group {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sync_request; } ;

/* Variables and functions */
 struct attribute_group md_redundancy_group ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pers_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (TYPE_2__*,struct attribute_group*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void mddev_unlock(struct mddev *mddev)
{
	if (mddev->to_remove) {
		/* These cannot be removed under reconfig_mutex as
		 * an access to the files will try to take reconfig_mutex
		 * while holding the file unremovable, which leads to
		 * a deadlock.
		 * So hold set sysfs_active while the remove in happeing,
		 * and anything else which might set ->to_remove or my
		 * otherwise change the sysfs namespace will fail with
		 * -EBUSY if sysfs_active is still set.
		 * We set sysfs_active under reconfig_mutex and elsewhere
		 * test it under the same mutex to ensure its correct value
		 * is seen.
		 */
		struct attribute_group *to_remove = mddev->to_remove;
		mddev->to_remove = NULL;
		mddev->sysfs_active = 1;
		mutex_unlock(&mddev->reconfig_mutex);

		if (mddev->kobj.sd) {
			if (to_remove != &md_redundancy_group)
				sysfs_remove_group(&mddev->kobj, to_remove);
			if (mddev->pers == NULL ||
			    mddev->pers->sync_request == NULL) {
				sysfs_remove_group(&mddev->kobj, &md_redundancy_group);
				if (mddev->sysfs_action)
					sysfs_put(mddev->sysfs_action);
				mddev->sysfs_action = NULL;
			}
		}
		mddev->sysfs_active = 0;
	} else
		mutex_unlock(&mddev->reconfig_mutex);

	/* As we've dropped the mutex we need a spinlock to
	 * make sure the thread doesn't disappear
	 */
	spin_lock(&pers_lock);
	md_wakeup_thread(mddev->thread);
	wake_up(&mddev->sb_wait);
	spin_unlock(&pers_lock);
}