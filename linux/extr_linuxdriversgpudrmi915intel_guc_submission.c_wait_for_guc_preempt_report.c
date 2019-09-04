#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_guc {struct guc_shared_ctx_data* shared_data_vaddr; } ;
struct intel_engine_cs {size_t guc_id; TYPE_1__* i915; } ;
struct guc_shared_ctx_data {struct guc_ctx_report* preempt_ctx_report; } ;
struct guc_ctx_report {scalar_t__ report_return_status; scalar_t__ affected_count; } ;
struct TYPE_2__ {struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_PREEMPT_POSTPROCESS_DELAY_MS ; 
 scalar_t__ INTEL_GUC_REPORT_STATUS_COMPLETE ; 
 scalar_t__ INTEL_GUC_REPORT_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_atomic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_for_guc_preempt_report(struct intel_engine_cs *engine)
{
	struct intel_guc *guc = &engine->i915->guc;
	struct guc_shared_ctx_data *data = guc->shared_data_vaddr;
	struct guc_ctx_report *report =
		&data->preempt_ctx_report[engine->guc_id];

	WARN_ON(wait_for_atomic(report->report_return_status ==
				INTEL_GUC_REPORT_STATUS_COMPLETE,
				GUC_PREEMPT_POSTPROCESS_DELAY_MS));
	/*
	 * GuC is expecting that we're also going to clear the affected context
	 * counter, let's also reset the return status to not depend on GuC
	 * resetting it after recieving another preempt action
	 */
	report->affected_count = 0;
	report->report_return_status = INTEL_GUC_REPORT_STATUS_UNKNOWN;
}