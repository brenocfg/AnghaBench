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
struct tx2_uncore_pmu {scalar_t__ cpu; scalar_t__ max_events; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ config; } ;
struct hw_perf_event {scalar_t__ config; } ;
struct perf_event {int attach_state; scalar_t__ cpu; TYPE_1__ attr; TYPE_2__* pmu; struct hw_perf_event hw; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int PERF_ATTACH_TASK ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 scalar_t__ nr_cpu_ids ; 
 struct tx2_uncore_pmu* pmu_to_tx2_pmu (TYPE_2__*) ; 
 int /*<<< orphan*/  tx2_uncore_validate_event_group (struct perf_event*) ; 

__attribute__((used)) static int tx2_uncore_event_init(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct tx2_uncore_pmu *tx2_pmu;

	/* Test the event attr type check for PMU enumeration */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/*
	 * SOC PMU counters are shared across all cores.
	 * Therefore, it does not support per-process mode.
	 * Also, it does not support event sampling mode.
	 */
	if (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	if (tx2_pmu->cpu >= nr_cpu_ids)
		return -EINVAL;
	event->cpu = tx2_pmu->cpu;

	if (event->attr.config >= tx2_pmu->max_events)
		return -EINVAL;

	/* store event id */
	hwc->config = event->attr.config;

	/* Validate the group */
	if (!tx2_uncore_validate_event_group(event))
		return -EINVAL;

	return 0;
}