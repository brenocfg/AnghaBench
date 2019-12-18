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
struct i915_sw_fence {int dummy; } ;
struct i915_sw_dma_fence_cb {int /*<<< orphan*/  base; struct i915_sw_fence* fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __dma_i915_sw_fence_wake (struct dma_fence*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_fence_assert (struct i915_sw_fence*) ; 
 int dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct dma_fence*,int /*<<< orphan*/ *)) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_await (struct i915_sw_fence*) ; 

int __i915_sw_fence_await_dma_fence(struct i915_sw_fence *fence,
				    struct dma_fence *dma,
				    struct i915_sw_dma_fence_cb *cb)
{
	int ret;

	debug_fence_assert(fence);

	if (dma_fence_is_signaled(dma))
		return 0;

	cb->fence = fence;
	i915_sw_fence_await(fence);

	ret = dma_fence_add_callback(dma, &cb->base, __dma_i915_sw_fence_wake);
	if (ret == 0) {
		ret = 1;
	} else {
		__dma_i915_sw_fence_wake(dma, &cb->base);
		if (ret == -ENOENT) /* fence already signaled */
			ret = 0;
	}

	return ret;
}