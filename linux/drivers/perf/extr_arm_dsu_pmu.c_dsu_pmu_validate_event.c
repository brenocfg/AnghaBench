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
struct perf_event {struct pmu* pmu; } ;
struct dsu_hw_events {int dummy; } ;

/* Variables and functions */
 scalar_t__ dsu_pmu_get_event_idx (struct dsu_hw_events*,struct perf_event*) ; 
 scalar_t__ is_software_event (struct perf_event*) ; 

__attribute__((used)) static bool dsu_pmu_validate_event(struct pmu *pmu,
				  struct dsu_hw_events *hw_events,
				  struct perf_event *event)
{
	if (is_software_event(event))
		return true;
	/* Reject groups spanning multiple HW PMUs. */
	if (event->pmu != pmu)
		return false;
	return dsu_pmu_get_event_idx(hw_events, event) >= 0;
}