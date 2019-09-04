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
typedef  scalar_t__ u64 ;
struct hw_perf_event {int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;

/* Variables and functions */
 scalar_t__ GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 scalar_t__ l2x0_pmu_counter_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ local64_xchg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  warn_if_saturated (scalar_t__) ; 

__attribute__((used)) static void l2x0_pmu_event_read(struct perf_event *event)
{
	struct hw_perf_event *hw = &event->hw;
	u64 prev_count, new_count, mask;

	do {
		 prev_count = local64_read(&hw->prev_count);
		 new_count = l2x0_pmu_counter_read(hw->idx);
	} while (local64_xchg(&hw->prev_count, new_count) != prev_count);

	mask = GENMASK_ULL(31, 0);
	local64_add((new_count - prev_count) & mask, &event->count);

	warn_if_saturated(new_count);
}