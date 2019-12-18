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
struct lock_class_key {int dummy; } ;
struct i915_sw_fence {unsigned long flags; scalar_t__ error; int /*<<< orphan*/  pending; int /*<<< orphan*/  wait; } ;
typedef  scalar_t__ i915_sw_fence_notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long I915_SW_FENCE_MASK ; 
 int /*<<< orphan*/  __init_waitqueue_head (int /*<<< orphan*/ *,char const*,struct lock_class_key*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug_fence_init (struct i915_sw_fence*) ; 

void __i915_sw_fence_init(struct i915_sw_fence *fence,
			  i915_sw_fence_notify_t fn,
			  const char *name,
			  struct lock_class_key *key)
{
	BUG_ON(!fn || (unsigned long)fn & ~I915_SW_FENCE_MASK);

	debug_fence_init(fence);

	__init_waitqueue_head(&fence->wait, name, key);
	atomic_set(&fence->pending, 1);
	fence->error = 0;

	fence->flags = (unsigned long)fn;
}