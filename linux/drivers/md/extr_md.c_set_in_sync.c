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
struct mddev {int in_sync; scalar_t__ sync_checkers; int safemode; int /*<<< orphan*/  writes_pending; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_SB_CHANGE_CLEAN ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_ref_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_to_atomic_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_to_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_in_sync(struct mddev *mddev)
{
	lockdep_assert_held(&mddev->lock);
	if (!mddev->in_sync) {
		mddev->sync_checkers++;
		spin_unlock(&mddev->lock);
		percpu_ref_switch_to_atomic_sync(&mddev->writes_pending);
		spin_lock(&mddev->lock);
		if (!mddev->in_sync &&
		    percpu_ref_is_zero(&mddev->writes_pending)) {
			mddev->in_sync = 1;
			/*
			 * Ensure ->in_sync is visible before we clear
			 * ->sync_checkers.
			 */
			smp_mb();
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
			sysfs_notify_dirent_safe(mddev->sysfs_state);
		}
		if (--mddev->sync_checkers == 0)
			percpu_ref_switch_to_percpu(&mddev->writes_pending);
	}
	if (mddev->safemode == 1)
		mddev->safemode = 0;
	return mddev->in_sync;
}