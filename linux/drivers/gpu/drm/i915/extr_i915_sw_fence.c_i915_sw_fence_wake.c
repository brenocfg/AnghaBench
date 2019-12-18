#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  private; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ wait_queue_entry_t ;

/* Variables and functions */
 int I915_SW_FENCE_FLAG_ALLOC ; 
 int /*<<< orphan*/  __i915_sw_fence_complete (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  i915_sw_fence_set_error_once (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_sw_fence_wake(wait_queue_entry_t *wq, unsigned mode, int flags, void *key)
{
	i915_sw_fence_set_error_once(wq->private, flags);

	list_del(&wq->entry);
	__i915_sw_fence_complete(wq->private, key);

	if (wq->flags & I915_SW_FENCE_FLAG_ALLOC)
		kfree(wq);
	return 0;
}