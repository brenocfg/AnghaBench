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
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {int num_fence_regs; struct drm_i915_fence_reg* fence_regs; TYPE_1__ drm; } ;
struct drm_i915_fence_reg {TYPE_2__* vma; } ;
struct TYPE_4__ {struct drm_i915_fence_reg* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_revoke_mmap (TYPE_2__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void i915_gem_revoke_fences(struct drm_i915_private *dev_priv)
{
	int i;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);

	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct drm_i915_fence_reg *fence = &dev_priv->fence_regs[i];

		GEM_BUG_ON(fence->vma && fence->vma->fence != fence);

		if (fence->vma)
			i915_vma_revoke_mmap(fence->vma);
	}
}