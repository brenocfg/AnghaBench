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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
struct xtensa_pmu_events {struct perf_event** event; int /*<<< orphan*/  used_mask; } ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int /*<<< orphan*/  last_period; } ;
struct perf_event {struct hw_perf_event hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int XCHAL_NUM_PERF_COUNTERS ; 
 int /*<<< orphan*/  XTENSA_PMU_PMSTAT (unsigned int) ; 
 int XTENSA_PMU_PMSTAT_OVFL ; 
 unsigned int find_first_bit (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int find_next_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int get_er (int /*<<< orphan*/ ) ; 
 struct pt_regs* get_irq_regs () ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_er (int,int /*<<< orphan*/ ) ; 
 struct xtensa_pmu_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ xtensa_perf_event_set_period (struct perf_event*,struct hw_perf_event*,unsigned int) ; 
 int /*<<< orphan*/  xtensa_perf_event_update (struct perf_event*,struct hw_perf_event*,unsigned int) ; 
 int /*<<< orphan*/  xtensa_pmu_events ; 
 int /*<<< orphan*/  xtensa_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

irqreturn_t xtensa_pmu_irq_handler(int irq, void *dev_id)
{
	irqreturn_t rc = IRQ_NONE;
	struct xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);
	unsigned i;

	for (i = find_first_bit(ev->used_mask, XCHAL_NUM_PERF_COUNTERS);
	     i < XCHAL_NUM_PERF_COUNTERS;
	     i = find_next_bit(ev->used_mask, XCHAL_NUM_PERF_COUNTERS, i + 1)) {
		uint32_t v = get_er(XTENSA_PMU_PMSTAT(i));
		struct perf_event *event = ev->event[i];
		struct hw_perf_event *hwc = &event->hw;
		u64 last_period;

		if (!(v & XTENSA_PMU_PMSTAT_OVFL))
			continue;

		set_er(v, XTENSA_PMU_PMSTAT(i));
		xtensa_perf_event_update(event, hwc, i);
		last_period = hwc->last_period;
		if (xtensa_perf_event_set_period(event, hwc, i)) {
			struct perf_sample_data data;
			struct pt_regs *regs = get_irq_regs();

			perf_sample_data_init(&data, 0, last_period);
			if (perf_event_overflow(event, &data, regs))
				xtensa_pmu_stop(event, 0);
		}

		rc = IRQ_HANDLED;
	}
	return rc;
}