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
struct i915_vma {struct drm_i915_fence_reg* fence; } ;
struct drm_i915_fence_reg {scalar_t__ pin_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int fence_update (struct drm_i915_fence_reg*,int /*<<< orphan*/ *) ; 

int i915_vma_put_fence(struct i915_vma *vma)
{
	struct drm_i915_fence_reg *fence = vma->fence;

	if (!fence)
		return 0;

	if (fence->pin_count)
		return -EBUSY;

	return fence_update(fence, NULL);
}