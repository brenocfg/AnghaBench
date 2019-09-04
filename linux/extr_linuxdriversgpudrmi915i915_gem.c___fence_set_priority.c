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
struct intel_engine_cs {int /*<<< orphan*/  (* schedule ) (struct i915_request*,struct i915_sched_attr const*) ;} ;
struct i915_sched_attr {int dummy; } ;
struct i915_request {struct intel_engine_cs* engine; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_is_i915 (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct i915_request*,struct i915_sched_attr const*) ; 
 struct i915_request* to_request (struct dma_fence*) ; 

__attribute__((used)) static void __fence_set_priority(struct dma_fence *fence,
				 const struct i915_sched_attr *attr)
{
	struct i915_request *rq;
	struct intel_engine_cs *engine;

	if (dma_fence_is_signaled(fence) || !dma_fence_is_i915(fence))
		return;

	rq = to_request(fence);
	engine = rq->engine;

	local_bh_disable();
	rcu_read_lock(); /* RCU serialisation for set-wedged protection */
	if (engine->schedule)
		engine->schedule(rq, attr);
	rcu_read_unlock();
	local_bh_enable(); /* kick the tasklets if queues were reprioritised */
}