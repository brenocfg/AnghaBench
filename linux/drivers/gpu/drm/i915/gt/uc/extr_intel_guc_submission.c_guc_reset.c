#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_execlists {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; struct intel_engine_execlists execlists; } ;
struct i915_request {int /*<<< orphan*/  head; int /*<<< orphan*/  hw_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_request_reset (struct i915_request*,int) ; 
 int /*<<< orphan*/  cancel_port_requests (struct intel_engine_execlists* const) ; 
 struct i915_request* execlists_unwind_incomplete_requests (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  i915_request_started (struct i915_request*) ; 
 int /*<<< orphan*/  intel_lr_context_reset (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void guc_reset(struct intel_engine_cs *engine, bool stalled)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_request *rq;
	unsigned long flags;

	spin_lock_irqsave(&engine->active.lock, flags);

	cancel_port_requests(execlists);

	/* Push back any incomplete requests for replay after the reset. */
	rq = execlists_unwind_incomplete_requests(execlists);
	if (!rq)
		goto out_unlock;

	if (!i915_request_started(rq))
		stalled = false;

	__i915_request_reset(rq, stalled);
	intel_lr_context_reset(engine, rq->hw_context, rq->head, stalled);

out_unlock:
	spin_unlock_irqrestore(&engine->active.lock, flags);
}