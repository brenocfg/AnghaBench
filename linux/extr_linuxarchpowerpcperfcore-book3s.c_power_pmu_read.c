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
struct TYPE_2__ {int state; int /*<<< orphan*/  period_left; int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  count; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ check_and_compute_delta (scalar_t__,scalar_t__) ; 
 scalar_t__ is_ebb_event (struct perf_event*) ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ read_pmc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void power_pmu_read(struct perf_event *event)
{
	s64 val, delta, prev;

	if (event->hw.state & PERF_HES_STOPPED)
		return;

	if (!event->hw.idx)
		return;

	if (is_ebb_event(event)) {
		val = read_pmc(event->hw.idx);
		local64_set(&event->hw.prev_count, val);
		return;
	}

	/*
	 * Performance monitor interrupts come even when interrupts
	 * are soft-disabled, as long as interrupts are hard-enabled.
	 * Therefore we treat them like NMIs.
	 */
	do {
		prev = local64_read(&event->hw.prev_count);
		barrier();
		val = read_pmc(event->hw.idx);
		delta = check_and_compute_delta(prev, val);
		if (!delta)
			return;
	} while (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	local64_add(delta, &event->count);

	/*
	 * A number of places program the PMC with (0x80000000 - period_left).
	 * We never want period_left to be less than 1 because we will program
	 * the PMC with a value >= 0x800000000 and an edge detected PMC will
	 * roll around to 0 before taking an exception. We have seen this
	 * on POWER8.
	 *
	 * To fix this, clamp the minimum value of period_left to 1.
	 */
	do {
		prev = local64_read(&event->hw.period_left);
		val = prev - delta;
		if (val < 1)
			val = 1;
	} while (local64_cmpxchg(&event->hw.period_left, prev, val) != prev);
}