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
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i915_sw_fence* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct i915_sw_fence* alloc_fence () ; 
 int /*<<< orphan*/  free_fence (struct i915_sw_fence*) ; 
 int i915_sw_fence_await_dma_fence (struct i915_sw_fence*,struct dma_fence*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_sw_fence_commit (struct i915_sw_fence*) ; 

__attribute__((used)) static struct i915_sw_fence *
wrap_dma_fence(struct dma_fence *dma, unsigned long delay)
{
	struct i915_sw_fence *fence;
	int err;

	fence = alloc_fence();
	if (!fence)
		return ERR_PTR(-ENOMEM);

	err = i915_sw_fence_await_dma_fence(fence, dma, delay, GFP_NOWAIT);
	i915_sw_fence_commit(fence);
	if (err < 0) {
		free_fence(fence);
		return ERR_PTR(err);
	}

	return fence;
}