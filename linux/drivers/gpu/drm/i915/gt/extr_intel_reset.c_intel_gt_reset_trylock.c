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
struct TYPE_2__ {int /*<<< orphan*/  backoff_srcu; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue; } ;
struct intel_gt {TYPE_1__ reset; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  I915_RESET_BACKOFF ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int intel_gt_reset_trylock(struct intel_gt *gt, int *srcu)
{
	might_lock(&gt->reset.backoff_srcu);
	might_sleep();

	rcu_read_lock();
	while (test_bit(I915_RESET_BACKOFF, &gt->reset.flags)) {
		rcu_read_unlock();

		if (wait_event_interruptible(gt->reset.queue,
					     !test_bit(I915_RESET_BACKOFF,
						       &gt->reset.flags)))
			return -EINTR;

		rcu_read_lock();
	}
	*srcu = srcu_read_lock(&gt->reset.backoff_srcu);
	rcu_read_unlock();

	return 0;
}