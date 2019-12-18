#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  priority; } ;
struct TYPE_8__ {scalar_t__ semaphores; TYPE_3__ attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_4__ sched; int /*<<< orphan*/  lock; TYPE_2__ fence; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_FENCE_FLAG_ACTIVE ; 
 int /*<<< orphan*/  I915_PRIORITY_NOSEMAPHORE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwsp_seqno (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_cancel_breadcrumb (struct i915_request*) ; 
 scalar_t__ i915_request_started (struct i915_request*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __i915_request_unsubmit(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;

	GEM_TRACE("%s fence %llx:%lld, current %d\n",
		  engine->name,
		  request->fence.context, request->fence.seqno,
		  hwsp_seqno(request));

	GEM_BUG_ON(!irqs_disabled());
	lockdep_assert_held(&engine->active.lock);

	/*
	 * Only unwind in reverse order, required so that the per-context list
	 * is kept in seqno/ring order.
	 */

	/* We may be recursing from the signal callback of another i915 fence */
	spin_lock_nested(&request->lock, SINGLE_DEPTH_NESTING);

	if (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &request->fence.flags))
		i915_request_cancel_breadcrumb(request);

	GEM_BUG_ON(!test_bit(I915_FENCE_FLAG_ACTIVE, &request->fence.flags));
	clear_bit(I915_FENCE_FLAG_ACTIVE, &request->fence.flags);

	spin_unlock(&request->lock);

	/* We've already spun, don't charge on resubmitting. */
	if (request->sched.semaphores && i915_request_started(request)) {
		request->sched.attr.priority |= I915_PRIORITY_NOSEMAPHORE;
		request->sched.semaphores = 0;
	}

	/*
	 * We don't need to wake_up any waiters on request->execute, they
	 * will get woken by any other event or us re-adding this request
	 * to the engine timeline (__i915_request_submit()). The waiters
	 * should be quite adapt at finding that the request now has a new
	 * global_seqno to the one they went to sleep on.
	 */
}