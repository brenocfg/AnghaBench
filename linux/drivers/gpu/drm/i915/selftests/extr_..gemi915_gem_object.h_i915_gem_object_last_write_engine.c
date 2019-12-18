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
struct intel_engine_cs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct dma_fence {int dummy; } ;
struct TYPE_4__ {struct intel_engine_cs* engine; } ;

/* Variables and functions */
 scalar_t__ dma_fence_is_i915 (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_2__* to_request (struct dma_fence*) ; 

__attribute__((used)) static inline struct intel_engine_cs *
i915_gem_object_last_write_engine(struct drm_i915_gem_object *obj)
{
	struct intel_engine_cs *engine = NULL;
	struct dma_fence *fence;

	rcu_read_lock();
	fence = dma_resv_get_excl_rcu(obj->base.resv);
	rcu_read_unlock();

	if (fence && dma_fence_is_i915(fence) && !dma_fence_is_signaled(fence))
		engine = to_request(fence)->engine;
	dma_fence_put(fence);

	return engine;
}