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
struct intel_engine_execlists {scalar_t__ queue_priority_hint; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __submit_queue_imm (struct intel_engine_cs*) ; 
 scalar_t__ rq_prio (struct i915_request const*) ; 

__attribute__((used)) static void submit_queue(struct intel_engine_cs *engine,
			 const struct i915_request *rq)
{
	struct intel_engine_execlists *execlists = &engine->execlists;

	if (rq_prio(rq) <= execlists->queue_priority_hint)
		return;

	execlists->queue_priority_hint = rq_prio(rq);
	__submit_queue_imm(engine);
}