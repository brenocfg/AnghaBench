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
struct TYPE_3__ {scalar_t__ type; scalar_t__ config; } ;
struct hw_perf_event {int idx; scalar_t__ config_base; } ;
struct perf_event {int attach_state; int cpu; TYPE_1__ attr; TYPE_2__* pmu; struct hw_perf_event hw; } ;
struct hisi_pmu {scalar_t__ check_event; int on_cpu; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  hisi_validate_event_group (struct perf_event*) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 struct hisi_pmu* to_hisi_pmu (TYPE_2__*) ; 

int hisi_uncore_pmu_event_init(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hisi_pmu *hisi_pmu;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/*
	 * We do not support sampling as the counters are all
	 * shared by all CPU cores in a CPU die(SCCL). Also we
	 * do not support attach to a task(per-process mode)
	 */
	if (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		return -EOPNOTSUPP;

	/*
	 *  The uncore counters not specific to any CPU, so cannot
	 *  support per-task
	 */
	if (event->cpu < 0)
		return -EINVAL;

	/*
	 * Validate if the events in group does not exceed the
	 * available counters in hardware.
	 */
	if (!hisi_validate_event_group(event))
		return -EINVAL;

	hisi_pmu = to_hisi_pmu(event->pmu);
	if (event->attr.config > hisi_pmu->check_event)
		return -EINVAL;

	if (hisi_pmu->on_cpu == -1)
		return -EINVAL;
	/*
	 * We don't assign an index until we actually place the event onto
	 * hardware. Use -1 to signify that we haven't decided where to put it
	 * yet.
	 */
	hwc->idx		= -1;
	hwc->config_base	= event->attr.config;

	/* Enforce to use the same CPU for all events in this PMU */
	event->cpu = hisi_pmu->on_cpu;

	return 0;
}