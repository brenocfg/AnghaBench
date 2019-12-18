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
struct TYPE_2__ {scalar_t__ idx; } ;
struct perf_event {TYPE_1__ hw; } ;
struct ddr_pmu {struct perf_event** events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ EVENT_CYCLES_COUNTER ; 
 int /*<<< orphan*/  EVENT_CYCLES_ID ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NUM_COUNTERS ; 
 int /*<<< orphan*/  ddr_perf_counter_enable (struct ddr_pmu*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ddr_perf_event_update (struct perf_event*) ; 

__attribute__((used)) static irqreturn_t ddr_perf_irq_handler(int irq, void *p)
{
	int i;
	struct ddr_pmu *pmu = (struct ddr_pmu *) p;
	struct perf_event *event, *cycle_event = NULL;

	/* all counter will stop if cycle counter disabled */
	ddr_perf_counter_enable(pmu,
			      EVENT_CYCLES_ID,
			      EVENT_CYCLES_COUNTER,
			      false);
	/*
	 * When the cycle counter overflows, all counters are stopped,
	 * and an IRQ is raised. If any other counter overflows, it
	 * continues counting, and no IRQ is raised.
	 *
	 * Cycles occur at least 4 times as often as other events, so we
	 * can update all events on a cycle counter overflow and not
	 * lose events.
	 *
	 */
	for (i = 0; i < NUM_COUNTERS; i++) {

		if (!pmu->events[i])
			continue;

		event = pmu->events[i];

		ddr_perf_event_update(event);

		if (event->hw.idx == EVENT_CYCLES_COUNTER)
			cycle_event = event;
	}

	ddr_perf_counter_enable(pmu,
			      EVENT_CYCLES_ID,
			      EVENT_CYCLES_COUNTER,
			      true);
	if (cycle_event)
		ddr_perf_event_update(cycle_event);

	return IRQ_HANDLED;
}