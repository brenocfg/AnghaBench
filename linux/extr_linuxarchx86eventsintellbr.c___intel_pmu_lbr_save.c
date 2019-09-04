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
typedef  int u64 ;
struct x86_perf_task_context {scalar_t__ lbr_callstack_users; int* lbr_from; int valid_lbrs; int tos; scalar_t__ log_id; int /*<<< orphan*/  lbr_stack_state; int /*<<< orphan*/ * lbr_info; int /*<<< orphan*/ * lbr_to; } ;
struct cpu_hw_events {scalar_t__ last_log_id; struct x86_perf_task_context* last_task_ctx; } ;
struct TYPE_3__ {scalar_t__ lbr_format; } ;
struct TYPE_4__ {int lbr_nr; TYPE_1__ intel_cap; } ;

/* Variables and functions */
 scalar_t__ LBR_FORMAT_INFO ; 
 int /*<<< orphan*/  LBR_NONE ; 
 int /*<<< orphan*/  LBR_VALID ; 
 scalar_t__ MSR_LBR_INFO_0 ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int intel_pmu_lbr_tos () ; 
 int rdlbr_from (unsigned int) ; 
 int /*<<< orphan*/  rdlbr_to (unsigned int) ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void __intel_pmu_lbr_save(struct x86_perf_task_context *task_ctx)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	unsigned lbr_idx, mask;
	u64 tos, from;
	int i;

	if (task_ctx->lbr_callstack_users == 0) {
		task_ctx->lbr_stack_state = LBR_NONE;
		return;
	}

	mask = x86_pmu.lbr_nr - 1;
	tos = intel_pmu_lbr_tos();
	for (i = 0; i < x86_pmu.lbr_nr; i++) {
		lbr_idx = (tos - i) & mask;
		from = rdlbr_from(lbr_idx);
		if (!from)
			break;
		task_ctx->lbr_from[i] = from;
		task_ctx->lbr_to[i]   = rdlbr_to(lbr_idx);
		if (x86_pmu.intel_cap.lbr_format == LBR_FORMAT_INFO)
			rdmsrl(MSR_LBR_INFO_0 + lbr_idx, task_ctx->lbr_info[i]);
	}
	task_ctx->valid_lbrs = i;
	task_ctx->tos = tos;
	task_ctx->lbr_stack_state = LBR_VALID;

	cpuc->last_task_ctx = task_ctx;
	cpuc->last_log_id = ++task_ctx->log_id;
}