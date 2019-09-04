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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct pmu_hw_events {struct perf_event** events; } ;
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int /*<<< orphan*/  last_period; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct arm_pmu {int num_events; int /*<<< orphan*/  (* disable ) (struct perf_event*) ;int /*<<< orphan*/  hw_events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  armpmu_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  armpmu_event_update (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_counter_has_overflowed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  armv8pmu_getreset_flags () ; 
 int /*<<< orphan*/  armv8pmu_has_overflowed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv8pmu_start (struct arm_pmu*) ; 
 int /*<<< orphan*/  armv8pmu_stop (struct arm_pmu*) ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  irq_work_run () ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t armv8pmu_handle_irq(struct arm_pmu *cpu_pmu)
{
	u32 pmovsr;
	struct perf_sample_data data;
	struct pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	struct pt_regs *regs;
	int idx;

	/*
	 * Get and reset the IRQ flags
	 */
	pmovsr = armv8pmu_getreset_flags();

	/*
	 * Did an overflow occur?
	 */
	if (!armv8pmu_has_overflowed(pmovsr))
		return IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

	/*
	 * Stop the PMU while processing the counter overflows
	 * to prevent skews in group events.
	 */
	armv8pmu_stop(cpu_pmu);
	for (idx = 0; idx < cpu_pmu->num_events; ++idx) {
		struct perf_event *event = cpuc->events[idx];
		struct hw_perf_event *hwc;

		/* Ignore if we don't have an event. */
		if (!event)
			continue;

		/*
		 * We have a single interrupt for all counters. Check that
		 * each counter has overflowed before we process it.
		 */
		if (!armv8pmu_counter_has_overflowed(pmovsr, idx))
			continue;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		if (!armpmu_event_set_period(event))
			continue;

		if (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	}
	armv8pmu_start(cpu_pmu);

	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with interrupts disabled. For
	 * platforms that can have the PMU interrupts raised as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	return IRQ_HANDLED;
}