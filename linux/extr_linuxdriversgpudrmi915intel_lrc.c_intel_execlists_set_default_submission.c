#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  prepare; } ;
struct TYPE_6__ {int /*<<< orphan*/  func; } ;
struct TYPE_7__ {TYPE_1__ tasklet; } ;
struct intel_engine_cs {TYPE_5__* i915; int /*<<< orphan*/  flags; int /*<<< orphan*/ * unpark; int /*<<< orphan*/ * park; TYPE_3__ reset; TYPE_2__ execlists; int /*<<< orphan*/  schedule; int /*<<< orphan*/  cancel_requests; int /*<<< orphan*/  submit_request; } ;
struct TYPE_9__ {int scheduler; } ;
struct TYPE_10__ {TYPE_4__ caps; scalar_t__ preempt_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_ENGINE_HAS_PREEMPTION ; 
 int /*<<< orphan*/  I915_ENGINE_SUPPORTS_STATS ; 
 int I915_SCHEDULER_CAP_ENABLED ; 
 int I915_SCHEDULER_CAP_PREEMPTION ; 
 int I915_SCHEDULER_CAP_PRIORITY ; 
 int /*<<< orphan*/  execlists_cancel_requests ; 
 int /*<<< orphan*/  execlists_reset_prepare ; 
 int /*<<< orphan*/  execlists_schedule ; 
 int /*<<< orphan*/  execlists_submission_tasklet ; 
 int /*<<< orphan*/  execlists_submit_request ; 
 scalar_t__ intel_engine_has_preemption (struct intel_engine_cs*) ; 

void intel_execlists_set_default_submission(struct intel_engine_cs *engine)
{
	engine->submit_request = execlists_submit_request;
	engine->cancel_requests = execlists_cancel_requests;
	engine->schedule = execlists_schedule;
	engine->execlists.tasklet.func = execlists_submission_tasklet;

	engine->reset.prepare = execlists_reset_prepare;

	engine->park = NULL;
	engine->unpark = NULL;

	engine->flags |= I915_ENGINE_SUPPORTS_STATS;
	if (engine->i915->preempt_context)
		engine->flags |= I915_ENGINE_HAS_PREEMPTION;

	engine->i915->caps.scheduler =
		I915_SCHEDULER_CAP_ENABLED |
		I915_SCHEDULER_CAP_PRIORITY;
	if (intel_engine_has_preemption(engine))
		engine->i915->caps.scheduler |= I915_SCHEDULER_CAP_PREEMPTION;
}