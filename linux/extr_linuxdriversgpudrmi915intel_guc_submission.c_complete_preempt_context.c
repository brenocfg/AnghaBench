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
struct intel_engine_execlists {int dummy; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_PREEMPT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_GEM_HWS_PREEMPT_INDEX ; 
 int /*<<< orphan*/  execlists_cancel_port_requests (struct intel_engine_execlists*) ; 
 int /*<<< orphan*/  execlists_is_active (struct intel_engine_execlists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_unwind_incomplete_requests (struct intel_engine_execlists*) ; 
 scalar_t__ inject_preempt_hang (struct intel_engine_execlists*) ; 
 int /*<<< orphan*/  intel_write_status_page (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_guc_preempt_report (struct intel_engine_cs*) ; 

__attribute__((used)) static void complete_preempt_context(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists *execlists = &engine->execlists;

	GEM_BUG_ON(!execlists_is_active(execlists, EXECLISTS_ACTIVE_PREEMPT));

	if (inject_preempt_hang(execlists))
		return;

	execlists_cancel_port_requests(execlists);
	execlists_unwind_incomplete_requests(execlists);

	wait_for_guc_preempt_report(engine);
	intel_write_status_page(engine, I915_GEM_HWS_PREEMPT_INDEX, 0);
}