#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {struct drm_i915_fence_reg* fence; TYPE_6__* obj; int /*<<< orphan*/  last_fence; } ;
struct drm_i915_fence_reg {TYPE_4__* i915; int /*<<< orphan*/  link; struct i915_vma* vma; } ;
struct TYPE_9__ {TYPE_1__* dev; } ;
struct TYPE_12__ {TYPE_2__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  fence_list; } ;
struct TYPE_11__ {TYPE_3__ mm; } ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fence_write (struct drm_i915_fence_reg*,struct i915_vma*) ; 
 int i915_gem_active_retire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_get_stride (TYPE_6__*) ; 
 int /*<<< orphan*/  i915_gem_object_get_tiling (TYPE_6__*) ; 
 int /*<<< orphan*/  i915_vma_flush_writes (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_is_map_and_fenceable (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_revoke_mmap (struct i915_vma*) ; 
 scalar_t__ intel_runtime_pm_get_if_in_use (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (TYPE_4__*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fence_update(struct drm_i915_fence_reg *fence,
			struct i915_vma *vma)
{
	int ret;

	if (vma) {
		if (!i915_vma_is_map_and_fenceable(vma))
			return -EINVAL;

		if (WARN(!i915_gem_object_get_stride(vma->obj) ||
			 !i915_gem_object_get_tiling(vma->obj),
			 "bogus fence setup with stride: 0x%x, tiling mode: %i\n",
			 i915_gem_object_get_stride(vma->obj),
			 i915_gem_object_get_tiling(vma->obj)))
			return -EINVAL;

		ret = i915_gem_active_retire(&vma->last_fence,
					     &vma->obj->base.dev->struct_mutex);
		if (ret)
			return ret;
	}

	if (fence->vma) {
		struct i915_vma *old = fence->vma;

		ret = i915_gem_active_retire(&old->last_fence,
					     &old->obj->base.dev->struct_mutex);
		if (ret)
			return ret;

		i915_vma_flush_writes(old);
	}

	if (fence->vma && fence->vma != vma) {
		/* Ensure that all userspace CPU access is completed before
		 * stealing the fence.
		 */
		GEM_BUG_ON(fence->vma->fence != fence);
		i915_vma_revoke_mmap(fence->vma);

		fence->vma->fence = NULL;
		fence->vma = NULL;

		list_move(&fence->link, &fence->i915->mm.fence_list);
	}

	/* We only need to update the register itself if the device is awake.
	 * If the device is currently powered down, we will defer the write
	 * to the runtime resume, see i915_gem_restore_fences().
	 */
	if (intel_runtime_pm_get_if_in_use(fence->i915)) {
		fence_write(fence, vma);
		intel_runtime_pm_put(fence->i915);
	}

	if (vma) {
		if (fence->vma != vma) {
			vma->fence = fence;
			fence->vma = vma;
		}

		list_move_tail(&fence->link, &fence->i915->mm.fence_list);
	}

	return 0;
}