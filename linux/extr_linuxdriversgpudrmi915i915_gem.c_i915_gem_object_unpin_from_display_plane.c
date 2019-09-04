#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {TYPE_4__* obj; int /*<<< orphan*/  display_alignment; TYPE_3__* vm; } ;
struct TYPE_8__ {scalar_t__ pin_global; } ;
struct TYPE_7__ {TYPE_2__* i915; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GTT_MIN_ALIGNMENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  i915_gem_object_bump_inactive_ggtt (TYPE_4__*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void
i915_gem_object_unpin_from_display_plane(struct i915_vma *vma)
{
	lockdep_assert_held(&vma->vm->i915->drm.struct_mutex);

	if (WARN_ON(vma->obj->pin_global == 0))
		return;

	if (--vma->obj->pin_global == 0)
		vma->display_alignment = I915_GTT_MIN_ALIGNMENT;

	/* Bump the LRU to try and avoid premature eviction whilst flipping  */
	i915_gem_object_bump_inactive_ggtt(vma->obj);

	i915_vma_unpin(vma);
}