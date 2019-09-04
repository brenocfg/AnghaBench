#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct x86_perf_task_context {int /*<<< orphan*/  lbr_callstack_users; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {TYPE_2__ branch_reg; } ;
struct perf_event {int /*<<< orphan*/  total_time_running; TYPE_1__* ctx; TYPE_3__ hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  lbr_users; int /*<<< orphan*/  br_sel; } ;
struct TYPE_8__ {int /*<<< orphan*/  lbr_nr; } ;
struct TYPE_5__ {int /*<<< orphan*/  pmu; struct x86_perf_task_context* task_ctx_data; } ;

/* Variables and functions */
 scalar_t__ branch_user_callstack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_lbr_reset () ; 
 int /*<<< orphan*/  perf_sched_cb_inc (int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_4__ x86_pmu ; 

void intel_pmu_lbr_add(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct x86_perf_task_context *task_ctx;

	if (!x86_pmu.lbr_nr)
		return;

	cpuc->br_sel = event->hw.branch_reg.reg;

	if (branch_user_callstack(cpuc->br_sel) && event->ctx->task_ctx_data) {
		task_ctx = event->ctx->task_ctx_data;
		task_ctx->lbr_callstack_users++;
	}

	/*
	 * Request pmu::sched_task() callback, which will fire inside the
	 * regular perf event scheduling, so that call will:
	 *
	 *  - restore or wipe; when LBR-callstack,
	 *  - wipe; otherwise,
	 *
	 * when this is from __perf_event_task_sched_in().
	 *
	 * However, if this is from perf_install_in_context(), no such callback
	 * will follow and we'll need to reset the LBR here if this is the
	 * first LBR event.
	 *
	 * The problem is, we cannot tell these cases apart... but we can
	 * exclude the biggest chunk of cases by looking at
	 * event->total_time_running. An event that has accrued runtime cannot
	 * be 'new'. Conversely, a new event can get installed through the
	 * context switch path for the first time.
	 */
	perf_sched_cb_inc(event->ctx->pmu);
	if (!cpuc->lbr_users++ && !event->total_time_running)
		intel_pmu_lbr_reset();
}