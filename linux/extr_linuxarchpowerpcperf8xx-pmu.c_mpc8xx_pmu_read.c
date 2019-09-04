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
struct TYPE_2__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  PERF_8xx_ID_CPU_CYCLES 131 
#define  PERF_8xx_ID_DTLB_LOAD_MISS 130 
#define  PERF_8xx_ID_HW_INSTRUCTIONS 129 
#define  PERF_8xx_ID_ITLB_LOAD_MISS 128 
 scalar_t__ dtlb_miss_counter ; 
 int event_type (struct perf_event*) ; 
 scalar_t__ get_insn_ctr () ; 
 scalar_t__ get_tb () ; 
 scalar_t__ itlb_miss_counter ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpc8xx_pmu_read(struct perf_event *event)
{
	int type = event_type(event);
	s64 prev, val = 0, delta = 0;

	if (type < 0)
		return;

	do {
		prev = local64_read(&event->hw.prev_count);
		switch (type) {
		case PERF_8xx_ID_CPU_CYCLES:
			val = get_tb();
			delta = 16 * (val - prev);
			break;
		case PERF_8xx_ID_HW_INSTRUCTIONS:
			val = get_insn_ctr();
			delta = prev - val;
			if (delta < 0)
				delta += 0x1000000000000LL;
			break;
		case PERF_8xx_ID_ITLB_LOAD_MISS:
			val = itlb_miss_counter;
			delta = (s64)((s32)val - (s32)prev);
			break;
		case PERF_8xx_ID_DTLB_LOAD_MISS:
			val = dtlb_miss_counter;
			delta = (s64)((s32)val - (s32)prev);
			break;
		}
	} while (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	local64_add(delta, &event->count);
}