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
struct drm_i915_gem_object {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_has_active_reference (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_is_active (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_set_active_reference (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void __i915_gem_object_release_unless_active(struct drm_i915_gem_object *obj)
{
	lockdep_assert_held(&obj->base.dev->struct_mutex);

	if (!i915_gem_object_has_active_reference(obj) &&
	    i915_gem_object_is_active(obj))
		i915_gem_object_set_active_reference(obj);
	else
		i915_gem_object_put(obj);
}