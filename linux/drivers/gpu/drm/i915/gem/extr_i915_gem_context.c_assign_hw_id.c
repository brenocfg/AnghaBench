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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 int __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int new_hw_id (struct drm_i915_private*,int) ; 
 int steal_hw_id (struct drm_i915_private*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int assign_hw_id(struct drm_i915_private *i915, unsigned int *out)
{
	int ret;

	lockdep_assert_held(&i915->contexts.mutex);

	/*
	 * We prefer to steal/stall ourselves and our users over that of the
	 * entire system. That may be a little unfair to our users, and
	 * even hurt high priority clients. The choice is whether to oomkill
	 * something else, or steal a context id.
	 */
	ret = new_hw_id(i915, GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	if (unlikely(ret < 0)) {
		ret = steal_hw_id(i915);
		if (ret < 0) /* once again for the correct errno code */
			ret = new_hw_id(i915, GFP_KERNEL);
		if (ret < 0)
			return ret;
	}

	*out = ret;
	return 0;
}