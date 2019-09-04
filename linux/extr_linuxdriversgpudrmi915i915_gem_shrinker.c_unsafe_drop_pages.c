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
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_MM_SHRINKER ; 
 int /*<<< orphan*/  __i915_gem_object_put_pages (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_unbind (struct drm_i915_gem_object*) ; 

__attribute__((used)) static bool unsafe_drop_pages(struct drm_i915_gem_object *obj)
{
	if (i915_gem_object_unbind(obj) == 0)
		__i915_gem_object_put_pages(obj, I915_MM_SHRINKER);
	return !i915_gem_object_has_pages(obj);
}