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
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  idle_work; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_1__ gt; } ;

/* Variables and functions */
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  drain_delayed_work (int /*<<< orphan*/ *) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fault_irq_set(struct drm_i915_private *i915,
	      unsigned long *irq,
	      unsigned long val)
{
	int err;

	err = mutex_lock_interruptible(&i915->drm.struct_mutex);
	if (err)
		return err;

	err = i915_gem_wait_for_idle(i915,
				     I915_WAIT_LOCKED |
				     I915_WAIT_INTERRUPTIBLE,
				     MAX_SCHEDULE_TIMEOUT);
	if (err)
		goto err_unlock;

	*irq = val;
	mutex_unlock(&i915->drm.struct_mutex);

	/* Flush idle worker to disarm irq */
	drain_delayed_work(&i915->gt.idle_work);

	return 0;

err_unlock:
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}