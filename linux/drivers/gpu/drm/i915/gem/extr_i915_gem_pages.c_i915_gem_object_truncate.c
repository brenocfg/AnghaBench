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
struct drm_i915_gem_object {TYPE_1__* ops; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* truncate ) (struct drm_i915_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_free_mmap_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_gem_object*) ; 

void i915_gem_object_truncate(struct drm_i915_gem_object *obj)
{
	drm_gem_free_mmap_offset(&obj->base);
	if (obj->ops->truncate)
		obj->ops->truncate(obj);
}