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
struct intel_engine_cs {int /*<<< orphan*/  gt; } ;
struct intel_context {struct intel_engine_cs* const engine; } ;
struct i915_request {struct intel_context* hw_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_CONTEXT_SCHEDULE_OUT ; 
 int /*<<< orphan*/  execlists_context_status_change (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context* const) ; 
 int /*<<< orphan*/  intel_engine_context_out (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  intel_gt_pm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kick_siblings (struct i915_request*,struct intel_context* const) ; 

__attribute__((used)) static inline void
__execlists_schedule_out(struct i915_request *rq,
			 struct intel_engine_cs * const engine)
{
	struct intel_context * const ce = rq->hw_context;

	intel_engine_context_out(engine);
	execlists_context_status_change(rq, INTEL_CONTEXT_SCHEDULE_OUT);
	intel_gt_pm_put(engine->gt);

	/*
	 * If this is part of a virtual engine, its next request may
	 * have been blocked waiting for access to the active context.
	 * We have to kick all the siblings again in case we need to
	 * switch (e.g. the next request is not runnable on this
	 * engine). Hopefully, we will already have submitted the next
	 * request before the tasklet runs and do not need to rebuild
	 * each virtual tree and kick everyone again.
	 */
	if (ce->engine != engine)
		kick_siblings(rq, ce);

	intel_context_put(ce);
}