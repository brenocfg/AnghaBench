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
struct i915_sched_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 unsigned int I915_WAIT_ALL ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int dma_resv_get_fences_rcu (int /*<<< orphan*/ ,struct dma_fence**,unsigned int*,struct dma_fence***) ; 
 int /*<<< orphan*/  fence_set_priority (struct dma_fence*,struct i915_sched_attr const*) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 

int
i915_gem_object_wait_priority(struct drm_i915_gem_object *obj,
			      unsigned int flags,
			      const struct i915_sched_attr *attr)
{
	struct dma_fence *excl;

	if (flags & I915_WAIT_ALL) {
		struct dma_fence **shared;
		unsigned int count, i;
		int ret;

		ret = dma_resv_get_fences_rcu(obj->base.resv,
							&excl, &count, &shared);
		if (ret)
			return ret;

		for (i = 0; i < count; i++) {
			fence_set_priority(shared[i], attr);
			dma_fence_put(shared[i]);
		}

		kfree(shared);
	} else {
		excl = dma_resv_get_excl_rcu(obj->base.resv);
	}

	if (excl) {
		fence_set_priority(excl, attr);
		dma_fence_put(excl);
	}
	return 0;
}