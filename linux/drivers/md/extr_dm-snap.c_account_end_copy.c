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
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ cow_threshold ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_1__*) ; 

__attribute__((used)) static void account_end_copy(struct dm_snapshot *s)
{
	spin_lock(&s->in_progress_wait.lock);
	BUG_ON(!s->in_progress);
	s->in_progress--;
	if (likely(s->in_progress <= cow_threshold) &&
	    unlikely(waitqueue_active(&s->in_progress_wait)))
		wake_up_locked(&s->in_progress_wait);
	spin_unlock(&s->in_progress_wait.lock);
}