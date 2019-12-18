#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  finish; int /*<<< orphan*/  reset; int /*<<< orphan*/  prepare; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; } ;
struct TYPE_6__ {TYPE_2__ tasklet; } ;
struct intel_engine_cs {scalar_t__ irq_disable; scalar_t__ irq_enable; int /*<<< orphan*/  flags; int /*<<< orphan*/  cancel_requests; TYPE_1__ reset; int /*<<< orphan*/ * unpark; int /*<<< orphan*/  park; TYPE_3__ execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_ENGINE_NEEDS_BREADCRUMB_TASKLET ; 
 int /*<<< orphan*/  I915_ENGINE_SUPPORTS_STATS ; 
 int /*<<< orphan*/  guc_cancel_requests ; 
 int /*<<< orphan*/  guc_reset ; 
 int /*<<< orphan*/  guc_reset_finish ; 
 int /*<<< orphan*/  guc_reset_prepare ; 
 int /*<<< orphan*/  guc_submission_tasklet ; 
 int /*<<< orphan*/  intel_execlists_set_default_submission (struct intel_engine_cs*) ; 

__attribute__((used)) static void guc_set_default_submission(struct intel_engine_cs *engine)
{
	/*
	 * We inherit a bunch of functions from execlists that we'd like
	 * to keep using:
	 *
	 *    engine->submit_request = execlists_submit_request;
	 *    engine->cancel_requests = execlists_cancel_requests;
	 *    engine->schedule = execlists_schedule;
	 *
	 * But we need to override the actual submission backend in order
	 * to talk to the GuC.
	 */
	intel_execlists_set_default_submission(engine);

	engine->execlists.tasklet.func = guc_submission_tasklet;

	/* do not use execlists park/unpark */
	engine->park = engine->unpark = NULL;

	engine->reset.prepare = guc_reset_prepare;
	engine->reset.reset = guc_reset;
	engine->reset.finish = guc_reset_finish;

	engine->cancel_requests = guc_cancel_requests;

	engine->flags &= ~I915_ENGINE_SUPPORTS_STATS;
	engine->flags |= I915_ENGINE_NEEDS_BREADCRUMB_TASKLET;

	/*
	 * For the breadcrumb irq to work we need the interrupts to stay
	 * enabled. However, on all platforms on which we'll have support for
	 * GuC submission we don't allow disabling the interrupts at runtime, so
	 * we're always safe with the current flow.
	 */
	GEM_BUG_ON(engine->irq_enable || engine->irq_disable);
}