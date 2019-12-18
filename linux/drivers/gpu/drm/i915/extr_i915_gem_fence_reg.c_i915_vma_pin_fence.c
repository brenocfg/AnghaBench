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
struct i915_vma {TYPE_2__* vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_1__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int __i915_vma_pin_fence (struct i915_vma*) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vma_is_ggtt (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_is_pinned (struct i915_vma*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_vma_pin_fence(struct i915_vma *vma)
{
	int err;

	/*
	 * Note that we revoke fences on runtime suspend. Therefore the user
	 * must keep the device awake whilst using the fence.
	 */
	assert_rpm_wakelock_held(&vma->vm->i915->runtime_pm);
	GEM_BUG_ON(!i915_vma_is_pinned(vma));
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));

	err = mutex_lock_interruptible(&vma->vm->mutex);
	if (err)
		return err;

	err = __i915_vma_pin_fence(vma);
	mutex_unlock(&vma->vm->mutex);

	return err;
}