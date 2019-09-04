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
struct TYPE_4__ {TYPE_1__* dev; } ;
struct drm_i915_gem_object {int cache_coherent; int read_domains; int /*<<< orphan*/  cache_dirty; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 unsigned int CLFLUSH_BEFORE ; 
 int ENODEV ; 
 int I915_BO_CACHE_COHERENT_FOR_READ ; 
 int I915_GEM_DOMAIN_CPU ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  X86_FEATURE_CLFLUSH ; 
 int /*<<< orphan*/  flush_write_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_has_struct_page (struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_cpu_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_wait (struct drm_i915_gem_object*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 

int i915_gem_obj_prepare_shmem_read(struct drm_i915_gem_object *obj,
				    unsigned int *needs_clflush)
{
	int ret;

	lockdep_assert_held(&obj->base.dev->struct_mutex);

	*needs_clflush = 0;
	if (!i915_gem_object_has_struct_page(obj))
		return -ENODEV;

	ret = i915_gem_object_wait(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_LOCKED,
				   MAX_SCHEDULE_TIMEOUT,
				   NULL);
	if (ret)
		return ret;

	ret = i915_gem_object_pin_pages(obj);
	if (ret)
		return ret;

	if (obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ ||
	    !static_cpu_has(X86_FEATURE_CLFLUSH)) {
		ret = i915_gem_object_set_to_cpu_domain(obj, false);
		if (ret)
			goto err_unpin;
		else
			goto out;
	}

	flush_write_domain(obj, ~I915_GEM_DOMAIN_CPU);

	/* If we're not in the cpu read domain, set ourself into the gtt
	 * read domain and manually flush cachelines (if required). This
	 * optimizes for the case when the gpu will dirty the data
	 * anyway again before the next pread happens.
	 */
	if (!obj->cache_dirty &&
	    !(obj->read_domains & I915_GEM_DOMAIN_CPU))
		*needs_clflush = CLFLUSH_BEFORE;

out:
	/* return with the pages pinned */
	return 0;

err_unpin:
	i915_gem_object_unpin_pages(obj);
	return ret;
}