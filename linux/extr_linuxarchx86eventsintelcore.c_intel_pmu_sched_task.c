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
struct perf_event_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pmu_lbr_sched_task (struct perf_event_context*,int) ; 
 int /*<<< orphan*/  intel_pmu_pebs_sched_task (struct perf_event_context*,int) ; 

__attribute__((used)) static void intel_pmu_sched_task(struct perf_event_context *ctx,
				 bool sched_in)
{
	intel_pmu_pebs_sched_task(ctx, sched_in);
	intel_pmu_lbr_sched_task(ctx, sched_in);
}