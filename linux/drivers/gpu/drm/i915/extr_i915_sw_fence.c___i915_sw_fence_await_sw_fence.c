#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; struct i915_sw_fence* private; int /*<<< orphan*/  (* func ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ wait_queue_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct i915_sw_fence {TYPE_5__ wait; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I915_SW_FENCE_FLAG_ALLOC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  debug_fence_assert (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_sw_fence_await (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_check_if_after (struct i915_sw_fence*,struct i915_sw_fence*) ; 
 scalar_t__ i915_sw_fence_done (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_set_error_once (struct i915_sw_fence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_sw_fence_wait (struct i915_sw_fence*) ; 
 int /*<<< orphan*/  i915_sw_fence_wake (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __i915_sw_fence_await_sw_fence(struct i915_sw_fence *fence,
					  struct i915_sw_fence *signaler,
					  wait_queue_entry_t *wq, gfp_t gfp)
{
	unsigned long flags;
	int pending;

	debug_fence_assert(fence);
	might_sleep_if(gfpflags_allow_blocking(gfp));

	if (i915_sw_fence_done(signaler)) {
		i915_sw_fence_set_error_once(fence, signaler->error);
		return 0;
	}

	debug_fence_assert(signaler);

	/* The dependency graph must be acyclic. */
	if (unlikely(i915_sw_fence_check_if_after(fence, signaler)))
		return -EINVAL;

	pending = 0;
	if (!wq) {
		wq = kmalloc(sizeof(*wq), gfp);
		if (!wq) {
			if (!gfpflags_allow_blocking(gfp))
				return -ENOMEM;

			i915_sw_fence_wait(signaler);
			i915_sw_fence_set_error_once(fence, signaler->error);
			return 0;
		}

		pending |= I915_SW_FENCE_FLAG_ALLOC;
	}

	INIT_LIST_HEAD(&wq->entry);
	wq->flags = pending;
	wq->func = i915_sw_fence_wake;
	wq->private = fence;

	i915_sw_fence_await(fence);

	spin_lock_irqsave(&signaler->wait.lock, flags);
	if (likely(!i915_sw_fence_done(signaler))) {
		__add_wait_queue_entry_tail(&signaler->wait, wq);
		pending = 1;
	} else {
		i915_sw_fence_wake(wq, 0, signaler->error, NULL);
		pending = 0;
	}
	spin_unlock_irqrestore(&signaler->wait.lock, flags);

	return pending;
}