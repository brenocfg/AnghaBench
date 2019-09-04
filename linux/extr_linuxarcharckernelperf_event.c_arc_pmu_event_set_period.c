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
typedef  int u64 ;
typedef  int u32 ;
struct hw_perf_event {int sample_period; int idx; int last_period; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  period_left; } ;
struct perf_event {struct hw_perf_event hw; } ;
typedef  int s64 ;
struct TYPE_2__ {int max_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_COUNTH ; 
 int /*<<< orphan*/  ARC_REG_PCT_COUNTL ; 
 int /*<<< orphan*/  ARC_REG_PCT_INDEX ; 
 TYPE_1__* arc_pmu ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arc_pmu_event_set_period(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	s64 left = local64_read(&hwc->period_left);
	s64 period = hwc->sample_period;
	int idx = hwc->idx;
	int overflow = 0;
	u64 value;

	if (unlikely(left <= -period)) {
		/* left underflowed by more than period. */
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	} else	if (unlikely(left <= 0)) {
		/* left underflowed by less than period. */
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	}

	if (left > arc_pmu->max_period)
		left = arc_pmu->max_period;

	value = arc_pmu->max_period - left;
	local64_set(&hwc->prev_count, value);

	/* Select counter */
	write_aux_reg(ARC_REG_PCT_INDEX, idx);

	/* Write value */
	write_aux_reg(ARC_REG_PCT_COUNTL, (u32)value);
	write_aux_reg(ARC_REG_PCT_COUNTH, (value >> 32));

	perf_event_update_userpage(event);

	return overflow;
}