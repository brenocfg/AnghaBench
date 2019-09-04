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
struct drm_i915_gem_object {TYPE_1__* ops; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I915_GEM_OBJECT_IS_SHRINKABLE ; 

__attribute__((used)) static inline bool
i915_gem_object_is_shrinkable(const struct drm_i915_gem_object *obj)
{
	return obj->ops->flags & I915_GEM_OBJECT_IS_SHRINKABLE;
}