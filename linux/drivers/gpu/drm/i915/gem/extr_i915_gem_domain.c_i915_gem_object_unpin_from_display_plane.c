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
struct i915_vma {int /*<<< orphan*/  display_alignment; struct drm_i915_gem_object* obj; } ;
struct drm_i915_gem_object {scalar_t__ pin_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GTT_MIN_ALIGNMENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_object_held (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_bump_inactive_ggtt (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 

void
i915_gem_object_unpin_from_display_plane(struct i915_vma *vma)
{
	struct drm_i915_gem_object *obj = vma->obj;

	assert_object_held(obj);

	if (WARN_ON(obj->pin_global == 0))
		return;

	if (--obj->pin_global == 0)
		vma->display_alignment = I915_GTT_MIN_ALIGNMENT;

	/* Bump the LRU to try and avoid premature eviction whilst flipping  */
	i915_gem_object_bump_inactive_ggtt(obj);

	i915_vma_unpin(vma);
}