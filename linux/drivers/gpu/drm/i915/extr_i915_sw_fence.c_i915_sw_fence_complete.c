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
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_sw_fence_complete (struct i915_sw_fence*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_fence_assert (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_done (struct i915_sw_fence*) ; 

void i915_sw_fence_complete(struct i915_sw_fence *fence)
{
	debug_fence_assert(fence);

	if (WARN_ON(i915_sw_fence_done(fence)))
		return;

	__i915_sw_fence_complete(fence, NULL);
}