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
struct drm_i915_gem_object {TYPE_2__ base; int /*<<< orphan*/  pin_global; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_gem_object_flush_for_display (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_object_flush_if_display(struct drm_i915_gem_object *obj)
{
	if (!READ_ONCE(obj->pin_global))
		return;

	mutex_lock(&obj->base.dev->struct_mutex);
	__i915_gem_object_flush_for_display(obj);
	mutex_unlock(&obj->base.dev->struct_mutex);
}