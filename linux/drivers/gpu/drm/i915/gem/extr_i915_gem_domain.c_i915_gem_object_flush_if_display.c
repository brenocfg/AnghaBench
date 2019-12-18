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
struct drm_i915_gem_object {int /*<<< orphan*/  pin_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_gem_object_flush_for_display (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 

void i915_gem_object_flush_if_display(struct drm_i915_gem_object *obj)
{
	if (!READ_ONCE(obj->pin_global))
		return;

	i915_gem_object_lock(obj);
	__i915_gem_object_flush_for_display(obj);
	i915_gem_object_unlock(obj);
}