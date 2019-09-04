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
struct cpu_hw_events {int n_pebs; } ;

/* Variables and functions */
 int pebs_needs_sched_cb (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  pebs_update_threshold (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  perf_sched_cb_dec (struct pmu*) ; 
 int /*<<< orphan*/  perf_sched_cb_inc (struct pmu*) ; 

__attribute__((used)) static void
pebs_update_state(bool needed_cb, struct cpu_hw_events *cpuc, struct pmu *pmu)
{
	/*
	 * Make sure we get updated with the first PEBS
	 * event. It will trigger also during removal, but
	 * that does not hurt:
	 */
	bool update = cpuc->n_pebs == 1;

	if (needed_cb != pebs_needs_sched_cb(cpuc)) {
		if (!needed_cb)
			perf_sched_cb_inc(pmu);
		else
			perf_sched_cb_dec(pmu);

		update = true;
	}

	if (update)
		pebs_update_threshold(cpuc);
}