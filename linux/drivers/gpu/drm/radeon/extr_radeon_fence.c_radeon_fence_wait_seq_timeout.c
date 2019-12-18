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
typedef  int /*<<< orphan*/  u64 ;
struct radeon_device {int /*<<< orphan*/  ddev; scalar_t__ needs_reset; int /*<<< orphan*/  fence_queue; } ;

/* Variables and functions */
 long EDEADLK ; 
 int RADEON_NUM_RINGS ; 
 scalar_t__ radeon_fence_any_seq_signaled (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_get (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_put (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trace_radeon_fence_wait_begin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_radeon_fence_wait_end (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,long) ; 

__attribute__((used)) static long radeon_fence_wait_seq_timeout(struct radeon_device *rdev,
					  u64 *target_seq, bool intr,
					  long timeout)
{
	long r;
	int i;

	if (radeon_fence_any_seq_signaled(rdev, target_seq))
		return timeout;

	/* enable IRQs and tracing */
	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		if (!target_seq[i])
			continue;

		trace_radeon_fence_wait_begin(rdev->ddev, i, target_seq[i]);
		radeon_irq_kms_sw_irq_get(rdev, i);
	}

	if (intr) {
		r = wait_event_interruptible_timeout(rdev->fence_queue, (
			radeon_fence_any_seq_signaled(rdev, target_seq)
			 || rdev->needs_reset), timeout);
	} else {
		r = wait_event_timeout(rdev->fence_queue, (
			radeon_fence_any_seq_signaled(rdev, target_seq)
			 || rdev->needs_reset), timeout);
	}

	if (rdev->needs_reset)
		r = -EDEADLK;

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		if (!target_seq[i])
			continue;

		radeon_irq_kms_sw_irq_put(rdev, i);
		trace_radeon_fence_wait_end(rdev->ddev, i, target_seq[i]);
	}

	return r;
}