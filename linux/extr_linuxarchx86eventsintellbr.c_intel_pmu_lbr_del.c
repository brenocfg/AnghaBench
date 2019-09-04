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
struct x86_perf_task_context {int /*<<< orphan*/  lbr_callstack_users; } ;
struct perf_event {TYPE_1__* ctx; } ;
struct cpu_hw_events {scalar_t__ lbr_users; int /*<<< orphan*/  br_sel; } ;
struct TYPE_4__ {int /*<<< orphan*/  lbr_nr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pmu; struct x86_perf_task_context* task_ctx_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ branch_user_callstack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_sched_cb_dec (int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_2__ x86_pmu ; 

void intel_pmu_lbr_del(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct x86_perf_task_context *task_ctx;

	if (!x86_pmu.lbr_nr)
		return;

	if (branch_user_callstack(cpuc->br_sel) &&
	    event->ctx->task_ctx_data) {
		task_ctx = event->ctx->task_ctx_data;
		task_ctx->lbr_callstack_users--;
	}

	cpuc->lbr_users--;
	WARN_ON_ONCE(cpuc->lbr_users < 0);
	perf_sched_cb_dec(event->ctx->pmu);
}