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
struct TYPE_6__ {int /*<<< orphan*/  prepare; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct TYPE_5__ {TYPE_1__ tasklet; } ;
struct intel_engine_cs {int /*<<< orphan*/  flags; TYPE_3__ reset; int /*<<< orphan*/  unpark; int /*<<< orphan*/  park; TYPE_2__ execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_ENGINE_SUPPORTS_STATS ; 
 int /*<<< orphan*/  guc_reset_prepare ; 
 int /*<<< orphan*/  guc_submission_park ; 
 int /*<<< orphan*/  guc_submission_tasklet ; 
 int /*<<< orphan*/  guc_submission_unpark ; 
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

	engine->park = guc_submission_park;
	engine->unpark = guc_submission_unpark;

	engine->reset.prepare = guc_reset_prepare;

	engine->flags &= ~I915_ENGINE_SUPPORTS_STATS;
}