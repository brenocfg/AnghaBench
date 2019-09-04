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
struct intel_fbdev {int vma_flags; TYPE_1__* fb; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned int ORIGIN_CPU ; 
 unsigned int ORIGIN_GTT ; 
 int PLANE_HAS_FENCE ; 
 struct drm_i915_gem_object* intel_fb_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fb_obj_invalidate (struct drm_i915_gem_object*,unsigned int) ; 

__attribute__((used)) static void intel_fbdev_invalidate(struct intel_fbdev *ifbdev)
{
	struct drm_i915_gem_object *obj = intel_fb_obj(&ifbdev->fb->base);
	unsigned int origin =
		ifbdev->vma_flags & PLANE_HAS_FENCE ? ORIGIN_GTT : ORIGIN_CPU;

	intel_fb_obj_invalidate(obj, origin);
}