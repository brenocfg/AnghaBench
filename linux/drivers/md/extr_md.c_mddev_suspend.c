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
struct mddev {int /*<<< orphan*/  safemode_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  sb_wait; TYPE_2__* pers; int /*<<< orphan*/  active_io; int /*<<< orphan*/  suspended; int /*<<< orphan*/  reconfig_mutex; TYPE_1__* thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;
struct TYPE_3__ {scalar_t__ tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_ALLOW_SB_UPDATE ; 
 int /*<<< orphan*/  MD_UPDATING_SB ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void mddev_suspend(struct mddev *mddev)
{
	WARN_ON_ONCE(mddev->thread && current == mddev->thread->tsk);
	lockdep_assert_held(&mddev->reconfig_mutex);
	if (mddev->suspended++)
		return;
	synchronize_rcu();
	wake_up(&mddev->sb_wait);
	set_bit(MD_ALLOW_SB_UPDATE, &mddev->flags);
	smp_mb__after_atomic();
	wait_event(mddev->sb_wait, atomic_read(&mddev->active_io) == 0);
	mddev->pers->quiesce(mddev, 1);
	clear_bit_unlock(MD_ALLOW_SB_UPDATE, &mddev->flags);
	wait_event(mddev->sb_wait, !test_bit(MD_UPDATING_SB, &mddev->flags));

	del_timer_sync(&mddev->safemode_timer);
}