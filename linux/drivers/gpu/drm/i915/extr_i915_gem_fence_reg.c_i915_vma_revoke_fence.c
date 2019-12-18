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
struct i915_vma {TYPE_1__* vm; struct i915_fence_reg* fence; } ;
struct i915_fence_reg {int /*<<< orphan*/  pin_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int fence_update (struct i915_fence_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int i915_vma_revoke_fence(struct i915_vma *vma)
{
	struct i915_fence_reg *fence = vma->fence;

	lockdep_assert_held(&vma->vm->mutex);
	if (!fence)
		return 0;

	if (atomic_read(&fence->pin_count))
		return -EBUSY;

	return fence_update(fence, NULL);
}