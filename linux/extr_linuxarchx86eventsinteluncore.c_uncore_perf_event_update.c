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
struct TYPE_2__ {int /*<<< orphan*/  prev_count; int /*<<< orphan*/  idx; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int local64_xchg (int /*<<< orphan*/ *,int) ; 
 int uncore_fixed_ctr_bits (struct intel_uncore_box*) ; 
 int uncore_freerunning_bits (struct intel_uncore_box*,struct perf_event*) ; 
 int uncore_perf_ctr_bits (struct intel_uncore_box*) ; 
 scalar_t__ uncore_pmc_fixed (int /*<<< orphan*/ ) ; 
 scalar_t__ uncore_pmc_freerunning (int /*<<< orphan*/ ) ; 
 int uncore_read_counter (struct intel_uncore_box*,struct perf_event*) ; 

void uncore_perf_event_update(struct intel_uncore_box *box, struct perf_event *event)
{
	u64 prev_count, new_count, delta;
	int shift;

	if (uncore_pmc_freerunning(event->hw.idx))
		shift = 64 - uncore_freerunning_bits(box, event);
	else if (uncore_pmc_fixed(event->hw.idx))
		shift = 64 - uncore_fixed_ctr_bits(box);
	else
		shift = 64 - uncore_perf_ctr_bits(box);

	/* the hrtimer might modify the previous event value */
again:
	prev_count = local64_read(&event->hw.prev_count);
	new_count = uncore_read_counter(box, event);
	if (local64_xchg(&event->hw.prev_count, new_count) != prev_count)
		goto again;

	delta = (new_count << shift) - (prev_count << shift);
	delta >>= shift;

	local64_add(delta, &event->count);
}