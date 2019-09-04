#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {struct drm_i915_fence_reg* fence; TYPE_3__* vm; int /*<<< orphan*/  obj; } ;
struct drm_i915_fence_reg {int pin_count; struct i915_vma* vma; TYPE_2__* i915; int /*<<< orphan*/  link; int /*<<< orphan*/  dirty; } ;
struct TYPE_6__ {int /*<<< orphan*/  i915; } ;
struct TYPE_4__ {int /*<<< orphan*/  fence_list; } ;
struct TYPE_5__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct drm_i915_fence_reg*) ; 
 int PTR_ERR (struct drm_i915_fence_reg*) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ ) ; 
 struct drm_i915_fence_reg* fence_find (int /*<<< orphan*/ ) ; 
 int fence_update (struct drm_i915_fence_reg*,struct i915_vma*) ; 
 scalar_t__ i915_gem_object_is_tiled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
i915_vma_pin_fence(struct i915_vma *vma)
{
	struct drm_i915_fence_reg *fence;
	struct i915_vma *set = i915_gem_object_is_tiled(vma->obj) ? vma : NULL;
	int err;

	/* Note that we revoke fences on runtime suspend. Therefore the user
	 * must keep the device awake whilst using the fence.
	 */
	assert_rpm_wakelock_held(vma->vm->i915);

	/* Just update our place in the LRU if our fence is getting reused. */
	if (vma->fence) {
		fence = vma->fence;
		GEM_BUG_ON(fence->vma != vma);
		fence->pin_count++;
		if (!fence->dirty) {
			list_move_tail(&fence->link,
				       &fence->i915->mm.fence_list);
			return 0;
		}
	} else if (set) {
		fence = fence_find(vma->vm->i915);
		if (IS_ERR(fence))
			return PTR_ERR(fence);

		GEM_BUG_ON(fence->pin_count);
		fence->pin_count++;
	} else
		return 0;

	err = fence_update(fence, set);
	if (err)
		goto out_unpin;

	GEM_BUG_ON(fence->vma != set);
	GEM_BUG_ON(vma->fence != (set ? fence : NULL));

	if (set)
		return 0;

out_unpin:
	fence->pin_count--;
	return err;
}