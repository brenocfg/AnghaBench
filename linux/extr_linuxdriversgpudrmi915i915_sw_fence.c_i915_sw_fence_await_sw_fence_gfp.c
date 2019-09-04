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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __i915_sw_fence_await_sw_fence (struct i915_sw_fence*,struct i915_sw_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int i915_sw_fence_await_sw_fence_gfp(struct i915_sw_fence *fence,
				     struct i915_sw_fence *signaler,
				     gfp_t gfp)
{
	return __i915_sw_fence_await_sw_fence(fence, signaler, NULL, gfp);
}