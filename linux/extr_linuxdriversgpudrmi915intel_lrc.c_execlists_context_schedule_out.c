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
struct i915_request {int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  execlists_context_status_change (struct i915_request*,unsigned long) ; 
 int /*<<< orphan*/  intel_engine_context_out (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_request_out (struct i915_request*) ; 

__attribute__((used)) static inline void
execlists_context_schedule_out(struct i915_request *rq, unsigned long status)
{
	intel_engine_context_out(rq->engine);
	execlists_context_status_change(rq, status);
	trace_i915_request_out(rq);
}