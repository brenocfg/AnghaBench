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
struct i915_vma {struct i915_fence_reg* fence; TYPE_1__* vm; int /*<<< orphan*/  obj; } ;
struct i915_ggtt {int /*<<< orphan*/  fence_list; } ;
struct i915_fence_reg {int /*<<< orphan*/  pin_count; struct i915_vma* vma; int /*<<< orphan*/  link; int /*<<< orphan*/  dirty; } ;
struct TYPE_2__ {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_fence_reg*) ; 
 int PTR_ERR (struct i915_fence_reg*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct i915_fence_reg* fence_find (int /*<<< orphan*/ ) ; 
 int fence_update (struct i915_fence_reg*,struct i915_vma*) ; 
 scalar_t__ i915_gem_object_is_tiled (int /*<<< orphan*/ ) ; 
 struct i915_ggtt* i915_vm_to_ggtt (TYPE_1__*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __i915_vma_pin_fence(struct i915_vma *vma)
{
	struct i915_ggtt *ggtt = i915_vm_to_ggtt(vma->vm);
	struct i915_fence_reg *fence;
	struct i915_vma *set = i915_gem_object_is_tiled(vma->obj) ? vma : NULL;
	int err;

	/* Just update our place in the LRU if our fence is getting reused. */
	if (vma->fence) {
		fence = vma->fence;
		GEM_BUG_ON(fence->vma != vma);
		atomic_inc(&fence->pin_count);
		if (!fence->dirty) {
			list_move_tail(&fence->link, &ggtt->fence_list);
			return 0;
		}
	} else if (set) {
		fence = fence_find(vma->vm->i915);
		if (IS_ERR(fence))
			return PTR_ERR(fence);

		GEM_BUG_ON(atomic_read(&fence->pin_count));
		atomic_inc(&fence->pin_count);
	} else {
		return 0;
	}

	err = fence_update(fence, set);
	if (err)
		goto out_unpin;

	GEM_BUG_ON(fence->vma != set);
	GEM_BUG_ON(vma->fence != (set ? fence : NULL));

	if (set)
		return 0;

out_unpin:
	atomic_dec(&fence->pin_count);
	return err;
}