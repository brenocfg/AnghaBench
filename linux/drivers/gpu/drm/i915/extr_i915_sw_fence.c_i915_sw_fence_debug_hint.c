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
struct i915_sw_fence {int flags; } ;

/* Variables and functions */
 int I915_SW_FENCE_MASK ; 

__attribute__((used)) static void *i915_sw_fence_debug_hint(void *addr)
{
	return (void *)(((struct i915_sw_fence *)addr)->flags & I915_SW_FENCE_MASK);
}