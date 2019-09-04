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
struct TYPE_3__ {int type; size_t config; scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;
struct hw_perf_event {scalar_t__ config; int /*<<< orphan*/  sample_period; int /*<<< orphan*/  period_left; int /*<<< orphan*/  last_period; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; } ;
struct TYPE_4__ {scalar_t__* ev_hw_idx; int /*<<< orphan*/  max_period; } ;

/* Variables and functions */
 scalar_t__ ARC_REG_PCT_CONFIG_KERN ; 
 scalar_t__ ARC_REG_PCT_CONFIG_USER ; 
 int ENOENT ; 
 size_t PERF_COUNT_HW_MAX ; 
#define  PERF_TYPE_HARDWARE 129 
#define  PERF_TYPE_HW_CACHE 128 
 TYPE_2__* arc_pmu ; 
 int arc_pmu_cache_event (size_t) ; 
 int /*<<< orphan*/ * arc_pmu_ev_hw_map ; 
 scalar_t__ is_isa_arcv2 () ; 
 int /*<<< orphan*/  is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 

__attribute__((used)) static int arc_pmu_event_init(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int ret;

	if (!is_sampling_event(event)) {
		hwc->sample_period  = arc_pmu->max_period;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	}

	hwc->config = 0;

	if (is_isa_arcv2()) {
		/* "exclude user" means "count only kernel" */
		if (event->attr.exclude_user)
			hwc->config |= ARC_REG_PCT_CONFIG_KERN;

		/* "exclude kernel" means "count only user" */
		if (event->attr.exclude_kernel)
			hwc->config |= ARC_REG_PCT_CONFIG_USER;
	}

	switch (event->attr.type) {
	case PERF_TYPE_HARDWARE:
		if (event->attr.config >= PERF_COUNT_HW_MAX)
			return -ENOENT;
		if (arc_pmu->ev_hw_idx[event->attr.config] < 0)
			return -ENOENT;
		hwc->config |= arc_pmu->ev_hw_idx[event->attr.config];
		pr_debug("init event %d with h/w %08x \'%s\'\n",
			 (int)event->attr.config, (int)hwc->config,
			 arc_pmu_ev_hw_map[event->attr.config]);
		return 0;

	case PERF_TYPE_HW_CACHE:
		ret = arc_pmu_cache_event(event->attr.config);
		if (ret < 0)
			return ret;
		hwc->config |= arc_pmu->ev_hw_idx[ret];
		pr_debug("init cache event with h/w %08x \'%s\'\n",
			 (int)hwc->config, arc_pmu_ev_hw_map[ret]);
		return 0;
	default:
		return -ENOENT;
	}
}