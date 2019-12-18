#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct dm_snapshot {scalar_t__ in_progress; TYPE_1__ in_progress_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __add_wait_queue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _origins_lock ; 
 scalar_t__ cow_threshold ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  io_schedule () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  remove_wait_queue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static bool wait_for_in_progress(struct dm_snapshot *s, bool unlock_origins)
{
	if (unlikely(s->in_progress > cow_threshold)) {
		spin_lock(&s->in_progress_wait.lock);
		if (likely(s->in_progress > cow_threshold)) {
			/*
			 * NOTE: this throttle doesn't account for whether
			 * the caller is servicing an IO that will trigger a COW
			 * so excess throttling may result for chunks not required
			 * to be COW'd.  But if cow_threshold was reached, extra
			 * throttling is unlikely to negatively impact performance.
			 */
			DECLARE_WAITQUEUE(wait, current);
			__add_wait_queue(&s->in_progress_wait, &wait);
			__set_current_state(TASK_UNINTERRUPTIBLE);
			spin_unlock(&s->in_progress_wait.lock);
			if (unlock_origins)
				up_read(&_origins_lock);
			io_schedule();
			remove_wait_queue(&s->in_progress_wait, &wait);
			return false;
		}
		spin_unlock(&s->in_progress_wait.lock);
	}
	return true;
}