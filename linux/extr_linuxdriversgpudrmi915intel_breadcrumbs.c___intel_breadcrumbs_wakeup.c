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
struct intel_wait {int /*<<< orphan*/  tsk; } ;
struct intel_breadcrumbs {struct intel_wait* irq_wait; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 unsigned int ENGINE_WAKEUP_ASLEEP ; 
 unsigned int ENGINE_WAKEUP_WAITER ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int task_asleep (int /*<<< orphan*/ ) ; 
 scalar_t__ wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __intel_breadcrumbs_wakeup(struct intel_breadcrumbs *b)
{
	struct intel_wait *wait;
	unsigned int result = 0;

	lockdep_assert_held(&b->irq_lock);

	wait = b->irq_wait;
	if (wait) {
		/*
		 * N.B. Since task_asleep() and ttwu are not atomic, the
		 * waiter may actually go to sleep after the check, causing
		 * us to suppress a valid wakeup. We prefer to reduce the
		 * number of false positive missed_breadcrumb() warnings
		 * at the expense of a few false negatives, as it it easy
		 * to trigger a false positive under heavy load. Enough
		 * signal should remain from genuine missed_breadcrumb()
		 * for us to detect in CI.
		 */
		bool was_asleep = task_asleep(wait->tsk);

		result = ENGINE_WAKEUP_WAITER;
		if (wake_up_process(wait->tsk) && was_asleep)
			result |= ENGINE_WAKEUP_ASLEEP;
	}

	return result;
}