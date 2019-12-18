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
struct TYPE_3__ {scalar_t__ type; } ;
struct hw_perf_event {int idx; scalar_t__ sample_period; } ;
struct perf_event {int /*<<< orphan*/  cpu; TYPE_2__* pmu; TYPE_1__ attr; struct hw_perf_event hw; } ;
struct l3cache_pmu {int /*<<< orphan*/  cpumask; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_l3_cache__validate_event_group (struct perf_event*) ; 
 struct l3cache_pmu* to_l3cache_pmu (TYPE_2__*) ; 

__attribute__((used)) static int qcom_l3_cache__event_init(struct perf_event *event)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	/*
	 * Is the event for this PMU?
	 */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/*
	 * Sampling not supported since these events are not core-attributable.
	 */
	if (hwc->sample_period)
		return -EINVAL;

	/*
	 * Task mode not available, we run the counters as socket counters,
	 * not attributable to any CPU and therefore cannot attribute per-task.
	 */
	if (event->cpu < 0)
		return -EINVAL;

	/* Validate the group */
	if (!qcom_l3_cache__validate_event_group(event))
		return -EINVAL;

	hwc->idx = -1;

	/*
	 * Many perf core operations (eg. events rotation) operate on a
	 * single CPU context. This is obvious for CPU PMUs, where one
	 * expects the same sets of events being observed on all CPUs,
	 * but can lead to issues for off-core PMUs, like this one, where
	 * each event could be theoretically assigned to a different CPU.
	 * To mitigate this, we enforce CPU assignment to one designated
	 * processor (the one described in the "cpumask" attribute exported
	 * by the PMU device). perf user space tools honor this and avoid
	 * opening more than one copy of the events.
	 */
	event->cpu = cpumask_first(&l3pmu->cpumask);

	return 0;
}