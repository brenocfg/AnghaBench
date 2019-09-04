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
struct hw_perf_event {unsigned long long idx; int flags; scalar_t__ sample_period; int /*<<< orphan*/  config; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct debug_store {int* pebs_event_reset; } ;
struct cpu_hw_events {unsigned long long pebs_enabled; struct debug_store* ds; } ;
struct TYPE_2__ {int cntval_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_INT ; 
 unsigned int INTEL_PMC_IDX_FIXED ; 
 unsigned int MAX_PEBS_EVENTS ; 
 int PERF_X86_EVENT_AUTO_RELOAD ; 
 int PERF_X86_EVENT_PEBS_LDLAT ; 
 int PERF_X86_EVENT_PEBS_ST ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

void intel_pmu_pebs_enable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	struct debug_store *ds = cpuc->ds;

	hwc->config &= ~ARCH_PERFMON_EVENTSEL_INT;

	cpuc->pebs_enabled |= 1ULL << hwc->idx;

	if (event->hw.flags & PERF_X86_EVENT_PEBS_LDLAT)
		cpuc->pebs_enabled |= 1ULL << (hwc->idx + 32);
	else if (event->hw.flags & PERF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabled |= 1ULL << 63;

	/*
	 * Use auto-reload if possible to save a MSR write in the PMI.
	 * This must be done in pmu::start(), because PERF_EVENT_IOC_PERIOD.
	 */
	if (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) {
		unsigned int idx = hwc->idx;

		if (idx >= INTEL_PMC_IDX_FIXED)
			idx = MAX_PEBS_EVENTS + (idx - INTEL_PMC_IDX_FIXED);
		ds->pebs_event_reset[idx] =
			(u64)(-hwc->sample_period) & x86_pmu.cntval_mask;
	} else {
		ds->pebs_event_reset[hwc->idx] = 0;
	}
}