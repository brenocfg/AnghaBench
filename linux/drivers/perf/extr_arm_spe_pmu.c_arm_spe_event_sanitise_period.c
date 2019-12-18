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
struct TYPE_2__ {int sample_period; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct arm_spe_pmu {int min_period; } ;

/* Variables and functions */
 int SYS_PMSIRR_EL1_INTERVAL_MASK ; 
 int SYS_PMSIRR_EL1_INTERVAL_SHIFT ; 
 struct arm_spe_pmu* to_spe_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_spe_event_sanitise_period(struct perf_event *event)
{
	struct arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	u64 period = event->hw.sample_period;
	u64 max_period = SYS_PMSIRR_EL1_INTERVAL_MASK
			 << SYS_PMSIRR_EL1_INTERVAL_SHIFT;

	if (period < spe_pmu->min_period)
		period = spe_pmu->min_period;
	else if (period > max_period)
		period = max_period;
	else
		period &= max_period;

	event->hw.sample_period = period;
}