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
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  shrink_list; } ;
struct TYPE_4__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_make_shrinkable (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 TYPE_2__* obj_to_i915 (struct drm_i915_gem_object*) ; 

void i915_gem_object_make_shrinkable(struct drm_i915_gem_object *obj)
{
	__i915_gem_object_make_shrinkable(obj,
					  &obj_to_i915(obj)->mm.shrink_list);
}