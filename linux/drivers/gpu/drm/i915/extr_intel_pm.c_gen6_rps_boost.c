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
struct intel_rps {scalar_t__ boost_freq; int /*<<< orphan*/  boosts; int /*<<< orphan*/  work; int /*<<< orphan*/  cur_freq; int /*<<< orphan*/  num_waiters; int /*<<< orphan*/  enabled; } ;
struct i915_request {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  fence; TYPE_2__* i915; } ;
struct TYPE_3__ {struct intel_rps rps; } ;
struct TYPE_4__ {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_REQUEST_WAITBOOST ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_is_signaled_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_has_waitboost (struct i915_request*) ; 
 scalar_t__ i915_request_signaled (struct i915_request*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gen6_rps_boost(struct i915_request *rq)
{
	struct intel_rps *rps = &rq->i915->gt_pm.rps;
	unsigned long flags;
	bool boost;

	/* This is intentionally racy! We peek at the state here, then
	 * validate inside the RPS worker.
	 */
	if (!rps->enabled)
		return;

	if (i915_request_signaled(rq))
		return;

	/* Serializes with i915_request_retire() */
	boost = false;
	spin_lock_irqsave(&rq->lock, flags);
	if (!i915_request_has_waitboost(rq) &&
	    !dma_fence_is_signaled_locked(&rq->fence)) {
		boost = !atomic_fetch_inc(&rps->num_waiters);
		rq->flags |= I915_REQUEST_WAITBOOST;
	}
	spin_unlock_irqrestore(&rq->lock, flags);
	if (!boost)
		return;

	if (READ_ONCE(rps->cur_freq) < rps->boost_freq)
		schedule_work(&rps->work);

	atomic_inc(&rps->boosts);
}