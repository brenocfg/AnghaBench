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
struct radeon_wait_cb {int /*<<< orphan*/  base; int /*<<< orphan*/  task; } ;
struct radeon_fence {struct radeon_device* rdev; } ;
struct radeon_device {scalar_t__ needs_reset; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 long EDEADLK ; 
 long ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_remove_callback (struct dma_fence*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_wait_cb ; 
 scalar_t__ radeon_test_signaled (struct radeon_fence*) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct radeon_fence* to_radeon_fence (struct dma_fence*) ; 

__attribute__((used)) static signed long radeon_fence_default_wait(struct dma_fence *f, bool intr,
					     signed long t)
{
	struct radeon_fence *fence = to_radeon_fence(f);
	struct radeon_device *rdev = fence->rdev;
	struct radeon_wait_cb cb;

	cb.task = current;

	if (dma_fence_add_callback(f, &cb.base, radeon_fence_wait_cb))
		return t;

	while (t > 0) {
		if (intr)
			set_current_state(TASK_INTERRUPTIBLE);
		else
			set_current_state(TASK_UNINTERRUPTIBLE);

		/*
		 * radeon_test_signaled must be called after
		 * set_current_state to prevent a race with wake_up_process
		 */
		if (radeon_test_signaled(fence))
			break;

		if (rdev->needs_reset) {
			t = -EDEADLK;
			break;
		}

		t = schedule_timeout(t);

		if (t > 0 && intr && signal_pending(current))
			t = -ERESTARTSYS;
	}

	__set_current_state(TASK_RUNNING);
	dma_fence_remove_callback(f, &cb.base);

	return t;
}