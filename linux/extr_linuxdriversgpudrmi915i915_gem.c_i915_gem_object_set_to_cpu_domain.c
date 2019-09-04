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
struct drm_i915_gem_object {int read_domains; int write_domain; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_CLFLUSH_SYNC ; 
 int I915_GEM_DOMAIN_CPU ; 
 int I915_WAIT_ALL ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  __start_cpu_write (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  flush_write_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_clflush_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_wait (struct drm_i915_gem_object*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int
i915_gem_object_set_to_cpu_domain(struct drm_i915_gem_object *obj, bool write)
{
	int ret;

	lockdep_assert_held(&obj->base.dev->struct_mutex);

	ret = i915_gem_object_wait(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_LOCKED |
				   (write ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT,
				   NULL);
	if (ret)
		return ret;

	flush_write_domain(obj, ~I915_GEM_DOMAIN_CPU);

	/* Flush the CPU cache if it's still invalid. */
	if ((obj->read_domains & I915_GEM_DOMAIN_CPU) == 0) {
		i915_gem_clflush_object(obj, I915_CLFLUSH_SYNC);
		obj->read_domains |= I915_GEM_DOMAIN_CPU;
	}

	/* It should now be out of any other write domains, and we can update
	 * the domain values for our changes.
	 */
	GEM_BUG_ON(obj->write_domain & ~I915_GEM_DOMAIN_CPU);

	/* If we're writing through the CPU, then the GPU read domains will
	 * need to be invalidated at next use.
	 */
	if (write)
		__start_cpu_write(obj);

	return 0;
}