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
struct i915_vma {int /*<<< orphan*/  obj; struct i915_fence_reg* fence; } ;
struct i915_fence_reg {int /*<<< orphan*/  vma; } ;
struct TYPE_2__ {int num_fences; struct i915_fence_reg* fence_regs; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 struct i915_vma* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fence_write (struct i915_fence_reg*,struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_is_tiled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void i915_gem_restore_fences(struct drm_i915_private *i915)
{
	int i;

	rcu_read_lock(); /* keep obj alive as we dereference */
	for (i = 0; i < i915->ggtt.num_fences; i++) {
		struct i915_fence_reg *reg = &i915->ggtt.fence_regs[i];
		struct i915_vma *vma = READ_ONCE(reg->vma);

		GEM_BUG_ON(vma && vma->fence != reg);

		/*
		 * Commit delayed tiling changes if we have an object still
		 * attached to the fence, otherwise just clear the fence.
		 */
		if (vma && !i915_gem_object_is_tiled(vma->obj))
			vma = NULL;

		fence_write(reg, vma);
	}
	rcu_read_unlock();
}