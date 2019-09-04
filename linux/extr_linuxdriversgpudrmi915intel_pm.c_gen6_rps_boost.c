#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_rps_client {int /*<<< orphan*/  boosts; } ;
struct intel_rps {scalar_t__ boost_freq; int /*<<< orphan*/  boosts; int /*<<< orphan*/  work; int /*<<< orphan*/  cur_freq; int /*<<< orphan*/  num_waiters; int /*<<< orphan*/  enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct i915_request {int waitboost; int /*<<< orphan*/  lock; TYPE_3__ fence; TYPE_2__* i915; } ;
struct TYPE_4__ {struct intel_rps rps; } ;
struct TYPE_5__ {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_is_signaled_locked (TYPE_3__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gen6_rps_boost(struct i915_request *rq,
		    struct intel_rps_client *rps_client)
{
	struct intel_rps *rps = &rq->i915->gt_pm.rps;
	unsigned long flags;
	bool boost;

	/* This is intentionally racy! We peek at the state here, then
	 * validate inside the RPS worker.
	 */
	if (!rps->enabled)
		return;

	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags))
		return;

	/* Serializes with i915_request_retire() */
	boost = false;
	spin_lock_irqsave(&rq->lock, flags);
	if (!rq->waitboost && !dma_fence_is_signaled_locked(&rq->fence)) {
		boost = !atomic_fetch_inc(&rps->num_waiters);
		rq->waitboost = true;
	}
	spin_unlock_irqrestore(&rq->lock, flags);
	if (!boost)
		return;

	if (READ_ONCE(rps->cur_freq) < rps->boost_freq)
		schedule_work(&rps->work);

	atomic_inc(rps_client ? &rps_client->boosts : &rps->boosts);
}