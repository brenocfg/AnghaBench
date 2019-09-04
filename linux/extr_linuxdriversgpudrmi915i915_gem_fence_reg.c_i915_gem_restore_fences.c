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
struct i915_vma {struct drm_i915_fence_reg* fence; int /*<<< orphan*/  obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  fence_list; } ;
struct drm_i915_private {int num_fence_regs; TYPE_1__ mm; struct drm_i915_fence_reg* fence_regs; } ;
struct drm_i915_fence_reg {struct i915_vma* vma; int /*<<< orphan*/  link; int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  fence_write (struct drm_i915_fence_reg*,struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_is_tiled (int /*<<< orphan*/ ) ; 
 int i915_vma_has_userfault (struct i915_vma*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void i915_gem_restore_fences(struct drm_i915_private *dev_priv)
{
	int i;

	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct drm_i915_fence_reg *reg = &dev_priv->fence_regs[i];
		struct i915_vma *vma = reg->vma;

		GEM_BUG_ON(vma && vma->fence != reg);

		/*
		 * Commit delayed tiling changes if we have an object still
		 * attached to the fence, otherwise just clear the fence.
		 */
		if (vma && !i915_gem_object_is_tiled(vma->obj)) {
			GEM_BUG_ON(!reg->dirty);
			GEM_BUG_ON(i915_vma_has_userfault(vma));

			list_move(&reg->link, &dev_priv->mm.fence_list);
			vma->fence = NULL;
			vma = NULL;
		}

		fence_write(reg, vma);
		reg->vma = vma;
	}
}