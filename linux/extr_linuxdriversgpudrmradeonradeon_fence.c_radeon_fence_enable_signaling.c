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
struct TYPE_4__ {int /*<<< orphan*/  func; int /*<<< orphan*/ * private; scalar_t__ flags; } ;
struct radeon_fence {size_t ring; scalar_t__ seq; int /*<<< orphan*/  base; TYPE_2__ fence_wake; struct radeon_device* rdev; } ;
struct radeon_device {int /*<<< orphan*/  fence_queue; TYPE_1__* fence_drv; int /*<<< orphan*/  exclusive_lock; } ;
struct dma_fence {int dummy; } ;
struct TYPE_3__ {int delayed_irq; int /*<<< orphan*/  last_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_TRACE (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  __add_wait_queue (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_fence_activity (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  radeon_fence_check_signaled ; 
 int /*<<< orphan*/  radeon_fence_schedule_check (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_get (struct radeon_device*,size_t) ; 
 scalar_t__ radeon_irq_kms_sw_irq_get_delayed (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_put (struct radeon_device*,size_t) ; 
 struct radeon_fence* to_radeon_fence (struct dma_fence*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool radeon_fence_enable_signaling(struct dma_fence *f)
{
	struct radeon_fence *fence = to_radeon_fence(f);
	struct radeon_device *rdev = fence->rdev;

	if (atomic64_read(&rdev->fence_drv[fence->ring].last_seq) >= fence->seq)
		return false;

	if (down_read_trylock(&rdev->exclusive_lock)) {
		radeon_irq_kms_sw_irq_get(rdev, fence->ring);

		if (radeon_fence_activity(rdev, fence->ring))
			wake_up_all_locked(&rdev->fence_queue);

		/* did fence get signaled after we enabled the sw irq? */
		if (atomic64_read(&rdev->fence_drv[fence->ring].last_seq) >= fence->seq) {
			radeon_irq_kms_sw_irq_put(rdev, fence->ring);
			up_read(&rdev->exclusive_lock);
			return false;
		}

		up_read(&rdev->exclusive_lock);
	} else {
		/* we're probably in a lockup, lets not fiddle too much */
		if (radeon_irq_kms_sw_irq_get_delayed(rdev, fence->ring))
			rdev->fence_drv[fence->ring].delayed_irq = true;
		radeon_fence_schedule_check(rdev, fence->ring);
	}

	fence->fence_wake.flags = 0;
	fence->fence_wake.private = NULL;
	fence->fence_wake.func = radeon_fence_check_signaled;
	__add_wait_queue(&rdev->fence_queue, &fence->fence_wake);
	dma_fence_get(f);

	DMA_FENCE_TRACE(&fence->base, "armed on ring %i!\n", fence->ring);
	return true;
}