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
struct drm_i915_gem_object {scalar_t__ write_domain; scalar_t__ cache_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_CLFLUSH_FORCE ; 
 int /*<<< orphan*/  I915_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  i915_gem_clflush_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_flush_write_domain (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __i915_gem_object_flush_for_display(struct drm_i915_gem_object *obj)
{
	/*
	 * We manually flush the CPU domain so that we can override and
	 * force the flush for the display, and perform it asyncrhonously.
	 */
	i915_gem_object_flush_write_domain(obj, ~I915_GEM_DOMAIN_CPU);
	if (obj->cache_dirty)
		i915_gem_clflush_object(obj, I915_CLFLUSH_FORCE);
	obj->write_domain = 0;
}