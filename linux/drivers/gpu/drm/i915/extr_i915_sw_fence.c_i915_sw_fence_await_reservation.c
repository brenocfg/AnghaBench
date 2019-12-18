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
struct dma_resv {int dummy; } ;
struct dma_fence_ops {int dummy; } ;
struct dma_fence {struct dma_fence_ops const* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_fence_assert (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl_rcu (struct dma_resv*) ; 
 int dma_resv_get_fences_rcu (struct dma_resv*,struct dma_fence**,unsigned int*,struct dma_fence***) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int i915_sw_fence_await_dma_fence (struct i915_sw_fence*,struct dma_fence*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 

int i915_sw_fence_await_reservation(struct i915_sw_fence *fence,
				    struct dma_resv *resv,
				    const struct dma_fence_ops *exclude,
				    bool write,
				    unsigned long timeout,
				    gfp_t gfp)
{
	struct dma_fence *excl;
	int ret = 0, pending;

	debug_fence_assert(fence);
	might_sleep_if(gfpflags_allow_blocking(gfp));

	if (write) {
		struct dma_fence **shared;
		unsigned int count, i;

		ret = dma_resv_get_fences_rcu(resv,
							&excl, &count, &shared);
		if (ret)
			return ret;

		for (i = 0; i < count; i++) {
			if (shared[i]->ops == exclude)
				continue;

			pending = i915_sw_fence_await_dma_fence(fence,
								shared[i],
								timeout,
								gfp);
			if (pending < 0) {
				ret = pending;
				break;
			}

			ret |= pending;
		}

		for (i = 0; i < count; i++)
			dma_fence_put(shared[i]);
		kfree(shared);
	} else {
		excl = dma_resv_get_excl_rcu(resv);
	}

	if (ret >= 0 && excl && excl->ops != exclude) {
		pending = i915_sw_fence_await_dma_fence(fence,
							excl,
							timeout,
							gfp);
		if (pending < 0)
			ret = pending;
		else
			ret |= pending;
	}

	dma_fence_put(excl);

	return ret;
}