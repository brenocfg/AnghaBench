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
struct tx2_uncore_pmu {scalar_t__ base; } ;
struct hw_perf_event {scalar_t__ event_base; scalar_t__ config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 scalar_t__ DMC_COUNTER_CTL ; 
 scalar_t__ DMC_COUNTER_DATA ; 
 int GET_COUNTERID (struct perf_event*) ; 

__attribute__((used)) static void init_cntr_base_dmc(struct perf_event *event,
		struct tx2_uncore_pmu *tx2_pmu)
{
	struct hw_perf_event *hwc = &event->hw;

	hwc->config_base = (unsigned long)tx2_pmu->base
		+ DMC_COUNTER_CTL;
	/* counter data reg offset at 0xc */
	hwc->event_base = (unsigned long)tx2_pmu->base
		+ DMC_COUNTER_DATA + (0xc * GET_COUNTERID(event));
}