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
struct intel_engine_execlists {struct i915_request** inflight; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; struct intel_engine_execlists execlists; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i915_request**) ; 
 int /*<<< orphan*/  __guc_dequeue (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  memmove (struct i915_request**,struct i915_request**,int) ; 
 int /*<<< orphan*/  schedule_out (struct i915_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void guc_submission_tasklet(unsigned long data)
{
	struct intel_engine_cs * const engine = (struct intel_engine_cs *)data;
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_request **port, *rq;
	unsigned long flags;

	spin_lock_irqsave(&engine->active.lock, flags);

	for (port = execlists->inflight; (rq = *port); port++) {
		if (!i915_request_completed(rq))
			break;

		schedule_out(rq);
	}
	if (port != execlists->inflight) {
		int idx = port - execlists->inflight;
		int rem = ARRAY_SIZE(execlists->inflight) - idx;
		memmove(execlists->inflight, port, rem * sizeof(*port));
	}

	__guc_dequeue(engine);

	spin_unlock_irqrestore(&engine->active.lock, flags);
}