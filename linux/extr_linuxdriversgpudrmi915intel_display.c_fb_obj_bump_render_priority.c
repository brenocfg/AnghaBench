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
struct i915_sched_attr {int /*<<< orphan*/  priority; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_PRIORITY_DISPLAY ; 
 int /*<<< orphan*/  i915_gem_object_wait_priority (struct drm_i915_gem_object*,int /*<<< orphan*/ ,struct i915_sched_attr*) ; 

__attribute__((used)) static void fb_obj_bump_render_priority(struct drm_i915_gem_object *obj)
{
	struct i915_sched_attr attr = {
		.priority = I915_PRIORITY_DISPLAY,
	};

	i915_gem_object_wait_priority(obj, 0, &attr);
}