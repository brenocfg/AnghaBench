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
struct pmu {int dummy; } ;
struct cpu_hw_events {int enabled; scalar_t__ n_events; int /*<<< orphan*/  idx_mask; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV67_PCTR_MODE_AGGREGATE ; 
 int /*<<< orphan*/  PERFMON_CMD_DESIRED_EVENTS ; 
 int /*<<< orphan*/  PERFMON_CMD_ENABLE ; 
 int /*<<< orphan*/  PERFMON_CMD_LOGGING_OPTIONS ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  maybe_change_configuration (struct cpu_hw_events*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrperfmon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alpha_pmu_enable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (cpuc->enabled)
		return;

	cpuc->enabled = 1;
	barrier();

	if (cpuc->n_events > 0) {
		/* Update cpuc with information from any new scheduled events. */
		maybe_change_configuration(cpuc);

		/* Start counting the desired events. */
		wrperfmon(PERFMON_CMD_LOGGING_OPTIONS, EV67_PCTR_MODE_AGGREGATE);
		wrperfmon(PERFMON_CMD_DESIRED_EVENTS, cpuc->config);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
	}
}