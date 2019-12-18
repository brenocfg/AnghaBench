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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct l3cache_pmu {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ L3_HML3_PM_EVCNTR (int) ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 struct l3cache_pmu* to_l3cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_l3_cache__64bit_counter_update(struct perf_event *event)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 hi, lo;
	u64 prev, new;

	do {
		prev = local64_read(&event->hw.prev_count);
		do {
			hi = readl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1));
			lo = readl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx));
		} while (hi != readl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1)));
		new = ((u64)hi << 32) | lo;
	} while (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	local64_add(new - prev, &event->count);
}