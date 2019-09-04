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
struct i915_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ __execlists_need_preempt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request const*) ; 
 scalar_t__ intel_engine_has_preemption (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  rq_prio (struct i915_request const*) ; 

__attribute__((used)) static inline bool need_preempt(const struct intel_engine_cs *engine,
				const struct i915_request *last,
				int prio)
{
	return (intel_engine_has_preemption(engine) &&
		__execlists_need_preempt(prio, rq_prio(last)) &&
		!i915_request_completed(last));
}