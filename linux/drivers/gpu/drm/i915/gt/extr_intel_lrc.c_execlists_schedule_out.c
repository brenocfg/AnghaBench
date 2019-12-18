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
struct i915_request {struct intel_context* hw_context; } ;

/* Variables and functions */
 struct intel_engine_cs* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __execlists_schedule_out (struct i915_request*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 struct intel_engine_cs* ptr_dec (struct intel_engine_cs*) ; 
 scalar_t__ ptr_unmask_bits (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  trace_i915_request_out (struct i915_request*) ; 
 int /*<<< orphan*/  try_cmpxchg (int /*<<< orphan*/ *,struct intel_engine_cs**,struct intel_engine_cs*) ; 

__attribute__((used)) static inline void
execlists_schedule_out(struct i915_request *rq)
{
	struct intel_context * const ce = rq->hw_context;
	struct intel_engine_cs *cur, *old;

	trace_i915_request_out(rq);

	old = READ_ONCE(ce->inflight);
	do
		cur = ptr_unmask_bits(old, 2) ? ptr_dec(old) : NULL;
	while (!try_cmpxchg(&ce->inflight, &old, cur));
	if (!cur)
		__execlists_schedule_out(rq, old);

	i915_request_put(rq);
}