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
struct dma_fence {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 scalar_t__ dma_fence_is_i915 (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,unsigned int,long) ; 
 long i915_request_wait (int /*<<< orphan*/ ,unsigned int,long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_request (struct dma_fence*) ; 

__attribute__((used)) static long
i915_gem_object_wait_fence(struct dma_fence *fence,
			   unsigned int flags,
			   long timeout)
{
	BUILD_BUG_ON(I915_WAIT_INTERRUPTIBLE != 0x1);

	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		return timeout;

	if (dma_fence_is_i915(fence))
		return i915_request_wait(to_request(fence), flags, timeout);

	return dma_fence_wait_timeout(fence,
				      flags & I915_WAIT_INTERRUPTIBLE,
				      timeout);
}