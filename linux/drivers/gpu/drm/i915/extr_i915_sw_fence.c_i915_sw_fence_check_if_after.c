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
struct i915_sw_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_SW_FENCE_CHECK_DAG ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int __i915_sw_fence_check_if_after (struct i915_sw_fence*,struct i915_sw_fence const* const) ; 
 int /*<<< orphan*/  __i915_sw_fence_clear_checked_bit (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool i915_sw_fence_check_if_after(struct i915_sw_fence *fence,
				  const struct i915_sw_fence * const signaler)
{
	unsigned long flags;
	bool err;

	if (!IS_ENABLED(CONFIG_DRM_I915_SW_FENCE_CHECK_DAG))
		return false;

	spin_lock_irqsave(&i915_sw_fence_lock, flags);
	err = __i915_sw_fence_check_if_after(fence, signaler);
	__i915_sw_fence_clear_checked_bit(fence);
	spin_unlock_irqrestore(&i915_sw_fence_lock, flags);

	return err;
}