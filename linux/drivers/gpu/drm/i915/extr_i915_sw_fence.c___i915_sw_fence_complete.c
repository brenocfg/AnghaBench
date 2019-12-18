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
struct list_head {int dummy; } ;
struct i915_sw_fence {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_FENCE_IDLE ; 
 int /*<<< orphan*/  DEBUG_FENCE_NOTIFY ; 
 int /*<<< orphan*/  FENCE_COMPLETE ; 
 int /*<<< orphan*/  FENCE_FREE ; 
 scalar_t__ NOTIFY_DONE ; 
 scalar_t__ __i915_sw_fence_notify (struct i915_sw_fence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_sw_fence_wake_up_all (struct i915_sw_fence*,struct list_head*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_fence_assert (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  debug_fence_destroy (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  debug_fence_set_state (struct i915_sw_fence*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __i915_sw_fence_complete(struct i915_sw_fence *fence,
				     struct list_head *continuation)
{
	debug_fence_assert(fence);

	if (!atomic_dec_and_test(&fence->pending))
		return;

	debug_fence_set_state(fence, DEBUG_FENCE_IDLE, DEBUG_FENCE_NOTIFY);

	if (__i915_sw_fence_notify(fence, FENCE_COMPLETE) != NOTIFY_DONE)
		return;

	debug_fence_set_state(fence, DEBUG_FENCE_NOTIFY, DEBUG_FENCE_IDLE);

	__i915_sw_fence_wake_up_all(fence, continuation);

	debug_fence_destroy(fence);
	__i915_sw_fence_notify(fence, FENCE_FREE);
}