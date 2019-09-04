#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ seqno; int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ timeline; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {scalar_t__ global_seqno; int /*<<< orphan*/  timeline; int /*<<< orphan*/  lock; TYPE_2__ fence; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int i915_seqno_passed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intel_engine_cancel_signaling (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_to_timeline (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __i915_request_unsubmit(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;

	GEM_TRACE("%s fence %llx:%d <- global=%d, current %d\n",
		  engine->name,
		  request->fence.context, request->fence.seqno,
		  request->global_seqno,
		  intel_engine_get_seqno(engine));

	GEM_BUG_ON(!irqs_disabled());
	lockdep_assert_held(&engine->timeline.lock);

	/*
	 * Only unwind in reverse order, required so that the per-context list
	 * is kept in seqno/ring order.
	 */
	GEM_BUG_ON(!request->global_seqno);
	GEM_BUG_ON(request->global_seqno != engine->timeline.seqno);
	GEM_BUG_ON(i915_seqno_passed(intel_engine_get_seqno(engine),
				     request->global_seqno));
	engine->timeline.seqno--;

	/* We may be recursing from the signal callback of another i915 fence */
	spin_lock_nested(&request->lock, SINGLE_DEPTH_NESTING);
	request->global_seqno = 0;
	if (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &request->fence.flags))
		intel_engine_cancel_signaling(request);
	spin_unlock(&request->lock);

	/* Transfer back from the global per-engine timeline to per-context */
	move_to_timeline(request, request->timeline);

	/*
	 * We don't need to wake_up any waiters on request->execute, they
	 * will get woken by any other event or us re-adding this request
	 * to the engine timeline (__i915_request_submit()). The waiters
	 * should be quite adapt at finding that the request now has a new
	 * global_seqno to the one they went to sleep on.
	 */
}