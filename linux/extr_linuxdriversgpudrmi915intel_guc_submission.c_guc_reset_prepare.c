#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_execlists {int /*<<< orphan*/  tasklet; } ;
struct intel_engine_cs {TYPE_2__* i915; int /*<<< orphan*/  name; struct intel_engine_execlists execlists; } ;
struct i915_request {int dummy; } ;
struct TYPE_3__ {scalar_t__ preempt_wq; } ;
struct TYPE_4__ {TYPE_1__ guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tasklet_disable_sync_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 struct i915_request* i915_gem_find_active_request (struct intel_engine_cs*) ; 

__attribute__((used)) static struct i915_request *
guc_reset_prepare(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	GEM_TRACE("%s\n", engine->name);

	/*
	 * Prevent request submission to the hardware until we have
	 * completed the reset in i915_gem_reset_finish(). If a request
	 * is completed by one engine, it may then queue a request
	 * to a second via its execlists->tasklet *just* as we are
	 * calling engine->init_hw() and also writing the ELSP.
	 * Turning off the execlists->tasklet until the reset is over
	 * prevents the race.
	 */
	__tasklet_disable_sync_once(&execlists->tasklet);

	/*
	 * We're using worker to queue preemption requests from the tasklet in
	 * GuC submission mode.
	 * Even though tasklet was disabled, we may still have a worker queued.
	 * Let's make sure that all workers scheduled before disabling the
	 * tasklet are completed before continuing with the reset.
	 */
	if (engine->i915->guc.preempt_wq)
		flush_workqueue(engine->i915->guc.preempt_wq);

	return i915_gem_find_active_request(engine);
}