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
struct mddev {int ro; int safemode; int /*<<< orphan*/  writes_pending; int /*<<< orphan*/  sb_flags; scalar_t__ suspended; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  has_superblocks; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; scalar_t__ in_sync; scalar_t__ sync_checkers; int /*<<< orphan*/  sync_thread; int /*<<< orphan*/  recovery; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_SB_CHANGE_CLEAN ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

bool md_write_start(struct mddev *mddev, struct bio *bi)
{
	int did_change = 0;

	if (bio_data_dir(bi) != WRITE)
		return true;

	BUG_ON(mddev->ro == 1);
	if (mddev->ro == 2) {
		/* need to switch to read/write */
		mddev->ro = 0;
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thread(mddev->thread);
		md_wakeup_thread(mddev->sync_thread);
		did_change = 1;
	}
	rcu_read_lock();
	percpu_ref_get(&mddev->writes_pending);
	smp_mb(); /* Match smp_mb in set_in_sync() */
	if (mddev->safemode == 1)
		mddev->safemode = 0;
	/* sync_checkers is always 0 when writes_pending is in per-cpu mode */
	if (mddev->in_sync || mddev->sync_checkers) {
		spin_lock(&mddev->lock);
		if (mddev->in_sync) {
			mddev->in_sync = 0;
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
			set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			md_wakeup_thread(mddev->thread);
			did_change = 1;
		}
		spin_unlock(&mddev->lock);
	}
	rcu_read_unlock();
	if (did_change)
		sysfs_notify_dirent_safe(mddev->sysfs_state);
	if (!mddev->has_superblocks)
		return true;
	wait_event(mddev->sb_wait,
		   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags) ||
		   mddev->suspended);
	if (test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) {
		percpu_ref_put(&mddev->writes_pending);
		return false;
	}
	return true;
}