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
struct mddev {int /*<<< orphan*/  sb_wait; scalar_t__ suspended; int /*<<< orphan*/  active_io; TYPE_1__* pers; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* make_request ) (struct mddev*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __wait ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_suspended (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void md_handle_request(struct mddev *mddev, struct bio *bio)
{
check_suspended:
	rcu_read_lock();
	if (is_suspended(mddev, bio)) {
		DEFINE_WAIT(__wait);
		for (;;) {
			prepare_to_wait(&mddev->sb_wait, &__wait,
					TASK_UNINTERRUPTIBLE);
			if (!is_suspended(mddev, bio))
				break;
			rcu_read_unlock();
			schedule();
			rcu_read_lock();
		}
		finish_wait(&mddev->sb_wait, &__wait);
	}
	atomic_inc(&mddev->active_io);
	rcu_read_unlock();

	if (!mddev->pers->make_request(mddev, bio)) {
		atomic_dec(&mddev->active_io);
		wake_up(&mddev->sb_wait);
		goto check_suspended;
	}

	if (atomic_dec_and_test(&mddev->active_io) && mddev->suspended)
		wake_up(&mddev->sb_wait);
}