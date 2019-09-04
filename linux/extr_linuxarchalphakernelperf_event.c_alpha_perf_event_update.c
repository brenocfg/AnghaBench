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
struct perf_event {int /*<<< orphan*/  count; } ;
struct hw_perf_event {int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; } ;
struct TYPE_2__ {long* pmc_count_mask; scalar_t__* pmc_max_period; } ;

/* Variables and functions */
 TYPE_1__* alpha_pmu ; 
 long alpha_read_pmc (int) ; 
 int /*<<< orphan*/  local64_add (long,int /*<<< orphan*/ *) ; 
 long local64_cmpxchg (int /*<<< orphan*/ *,long,long) ; 
 long local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (long,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long alpha_perf_event_update(struct perf_event *event,
					struct hw_perf_event *hwc, int idx, long ovf)
{
	long prev_raw_count, new_raw_count;
	long delta;

again:
	prev_raw_count = local64_read(&hwc->prev_count);
	new_raw_count = alpha_read_pmc(idx);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		goto again;

	delta = (new_raw_count - (prev_raw_count & alpha_pmu->pmc_count_mask[idx])) + ovf;

	/* It is possible on very rare occasions that the PMC has overflowed
	 * but the interrupt is yet to come.  Detect and fix this situation.
	 */
	if (unlikely(delta < 0)) {
		delta += alpha_pmu->pmc_max_period[idx] + 1;
	}

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	return new_raw_count;
}