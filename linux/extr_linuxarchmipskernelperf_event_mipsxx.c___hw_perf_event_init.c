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
struct perf_event_attr {scalar_t__ type; scalar_t__ config; int /*<<< orphan*/  exclude_hv; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_user; } ;
struct hw_perf_event {int idx; scalar_t__ sample_period; int /*<<< orphan*/  period_left; scalar_t__ last_period; scalar_t__ config; int /*<<< orphan*/  config_base; int /*<<< orphan*/  event_base; } ;
struct perf_event {int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;struct perf_event* group_leader; struct perf_event_attr attr; struct hw_perf_event hw; } ;
struct mips_perf_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_period; struct mips_perf_event* (* map_raw_event ) (scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct mips_perf_event const*) ; 
 int /*<<< orphan*/  MIPS_PERFCTRL_EXL ; 
 int /*<<< orphan*/  MIPS_PERFCTRL_IE ; 
 int /*<<< orphan*/  MIPS_PERFCTRL_K ; 
 int /*<<< orphan*/  MIPS_PERFCTRL_S ; 
 int /*<<< orphan*/  MIPS_PERFCTRL_U ; 
 int /*<<< orphan*/  M_PERFCTL_CONFIG_MASK ; 
 scalar_t__ PERF_COUNT_HW_MAX ; 
 scalar_t__ PERF_TYPE_HARDWARE ; 
 scalar_t__ PERF_TYPE_HW_CACHE ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int PTR_ERR (struct mips_perf_event const*) ; 
 int /*<<< orphan*/  hw_perf_event_destroy (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ mipspmu ; 
 struct mips_perf_event* mipspmu_map_cache_event (scalar_t__) ; 
 struct mips_perf_event* mipspmu_map_general_event (scalar_t__) ; 
 int /*<<< orphan*/  mipspmu_perf_event_encode (struct mips_perf_event const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_event_mutex ; 
 struct mips_perf_event* stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*) ; 
 int validate_group (struct perf_event*) ; 

__attribute__((used)) static int __hw_perf_event_init(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	const struct mips_perf_event *pev;
	int err;

	/* Returning MIPS event descriptor for generic perf event. */
	if (PERF_TYPE_HARDWARE == event->attr.type) {
		if (event->attr.config >= PERF_COUNT_HW_MAX)
			return -EINVAL;
		pev = mipspmu_map_general_event(event->attr.config);
	} else if (PERF_TYPE_HW_CACHE == event->attr.type) {
		pev = mipspmu_map_cache_event(event->attr.config);
	} else if (PERF_TYPE_RAW == event->attr.type) {
		/* We are working on the global raw event. */
		mutex_lock(&raw_event_mutex);
		pev = mipspmu.map_raw_event(event->attr.config);
	} else {
		/* The event type is not (yet) supported. */
		return -EOPNOTSUPP;
	}

	if (IS_ERR(pev)) {
		if (PERF_TYPE_RAW == event->attr.type)
			mutex_unlock(&raw_event_mutex);
		return PTR_ERR(pev);
	}

	/*
	 * We allow max flexibility on how each individual counter shared
	 * by the single CPU operates (the mode exclusion and the range).
	 */
	hwc->config_base = MIPS_PERFCTRL_IE;

	hwc->event_base = mipspmu_perf_event_encode(pev);
	if (PERF_TYPE_RAW == event->attr.type)
		mutex_unlock(&raw_event_mutex);

	if (!attr->exclude_user)
		hwc->config_base |= MIPS_PERFCTRL_U;
	if (!attr->exclude_kernel) {
		hwc->config_base |= MIPS_PERFCTRL_K;
		/* MIPS kernel mode: KSU == 00b || EXL == 1 || ERL == 1 */
		hwc->config_base |= MIPS_PERFCTRL_EXL;
	}
	if (!attr->exclude_hv)
		hwc->config_base |= MIPS_PERFCTRL_S;

	hwc->config_base &= M_PERFCTL_CONFIG_MASK;
	/*
	 * The event can belong to another cpu. We do not assign a local
	 * counter for it for now.
	 */
	hwc->idx = -1;
	hwc->config = 0;

	if (!hwc->sample_period) {
		hwc->sample_period  = mipspmu.max_period;
		hwc->last_period    = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	}

	err = 0;
	if (event->group_leader != event)
		err = validate_group(event);

	event->destroy = hw_perf_event_destroy;

	if (err)
		event->destroy(event);

	return err;
}