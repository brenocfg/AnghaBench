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
struct pmu_hw_events {int dummy; } ;
struct pmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_on_exec; } ;
struct perf_event {scalar_t__ state; struct pmu* pmu; TYPE_1__ attr; } ;
struct arm_pmu {scalar_t__ (* get_event_idx ) (struct pmu_hw_events*,struct perf_event*) ;} ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 scalar_t__ is_software_event (struct perf_event*) ; 
 scalar_t__ stub1 (struct pmu_hw_events*,struct perf_event*) ; 
 struct arm_pmu* to_arm_pmu (struct pmu*) ; 

__attribute__((used)) static int
validate_event(struct pmu *pmu, struct pmu_hw_events *hw_events,
			       struct perf_event *event)
{
	struct arm_pmu *armpmu;

	if (is_software_event(event))
		return 1;

	/*
	 * Reject groups spanning multiple HW PMUs (e.g. CPU + CCI). The
	 * core perf code won't check that the pmu->ctx == leader->ctx
	 * until after pmu->event_init(event).
	 */
	if (event->pmu != pmu)
		return 0;

	if (event->state < PERF_EVENT_STATE_OFF)
		return 1;

	if (event->state == PERF_EVENT_STATE_OFF && !event->attr.enable_on_exec)
		return 1;

	armpmu = to_arm_pmu(event->pmu);
	return armpmu->get_event_idx(hw_events, event) >= 0;
}