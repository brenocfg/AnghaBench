#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {int cache_dirty; int cache_coherent; scalar_t__ write_domain; TYPE_2__ mm; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  chain; } ;
struct clflush {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_BO_CACHE_COHERENT_FOR_READ ; 
 unsigned int I915_CLFLUSH_FORCE ; 
 unsigned int I915_CLFLUSH_SYNC ; 
 int /*<<< orphan*/  I915_FENCE_GFP ; 
 int /*<<< orphan*/  I915_FENCE_TIMEOUT ; 
 scalar_t__ I915_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  __do_clflush (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  assert_object_held (struct drm_i915_gem_object*) ; 
 struct clflush* clflush_work_create (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  dma_fence_work_commit (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_has_struct_page (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_sw_fence_await_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_gem_object_clflush (struct drm_i915_gem_object*) ; 

bool i915_gem_clflush_object(struct drm_i915_gem_object *obj,
			     unsigned int flags)
{
	struct clflush *clflush;

	assert_object_held(obj);

	/*
	 * Stolen memory is always coherent with the GPU as it is explicitly
	 * marked as wc by the system, or the system is cache-coherent.
	 * Similarly, we only access struct pages through the CPU cache, so
	 * anything not backed by physical memory we consider to be always
	 * coherent and not need clflushing.
	 */
	if (!i915_gem_object_has_struct_page(obj)) {
		obj->cache_dirty = false;
		return false;
	}

	/* If the GPU is snooping the contents of the CPU cache,
	 * we do not need to manually clear the CPU cache lines.  However,
	 * the caches are only snooped when the render cache is
	 * flushed/invalidated.  As we always have to emit invalidations
	 * and flushes when moving into and out of the RENDER domain, correct
	 * snooping behaviour occurs naturally as the result of our domain
	 * tracking.
	 */
	if (!(flags & I915_CLFLUSH_FORCE) &&
	    obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ)
		return false;

	trace_i915_gem_object_clflush(obj);

	clflush = NULL;
	if (!(flags & I915_CLFLUSH_SYNC))
		clflush = clflush_work_create(obj);
	if (clflush) {
		i915_sw_fence_await_reservation(&clflush->base.chain,
						obj->base.resv, NULL, true,
						I915_FENCE_TIMEOUT,
						I915_FENCE_GFP);
		dma_resv_add_excl_fence(obj->base.resv, &clflush->base.dma);
		dma_fence_work_commit(&clflush->base);
	} else if (obj->mm.pages) {
		__do_clflush(obj);
	} else {
		GEM_BUG_ON(obj->write_domain != I915_GEM_DOMAIN_CPU);
	}

	obj->cache_dirty = false;
	return true;
}