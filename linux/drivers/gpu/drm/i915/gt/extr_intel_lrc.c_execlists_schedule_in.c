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
struct intel_engine_cs {int dummy; } ;
struct intel_context {int /*<<< orphan*/  inflight; } ;
struct i915_request {scalar_t__ engine; struct intel_context* hw_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct intel_engine_cs* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __execlists_schedule_in (struct i915_request*) ; 
 struct i915_request* i915_request_get (struct i915_request*) ; 
 scalar_t__ intel_context_inflight (struct intel_context* const) ; 
 int /*<<< orphan*/  intel_engine_pm_is_awake (scalar_t__) ; 
 int /*<<< orphan*/  ptr_inc (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  trace_i915_request_in (struct i915_request*,int) ; 
 int /*<<< orphan*/  try_cmpxchg (int /*<<< orphan*/ *,struct intel_engine_cs**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct i915_request *
execlists_schedule_in(struct i915_request *rq, int idx)
{
	struct intel_context * const ce = rq->hw_context;
	struct intel_engine_cs *old;

	GEM_BUG_ON(!intel_engine_pm_is_awake(rq->engine));
	trace_i915_request_in(rq, idx);

	old = READ_ONCE(ce->inflight);
	do {
		if (!old) {
			WRITE_ONCE(ce->inflight, __execlists_schedule_in(rq));
			break;
		}
	} while (!try_cmpxchg(&ce->inflight, &old, ptr_inc(old)));

	GEM_BUG_ON(intel_context_inflight(ce) != rq->engine);
	return i915_request_get(rq);
}