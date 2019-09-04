#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_2__ hw; } ;
struct TYPE_3__ {scalar_t__ cd; scalar_t__ cs; } ;
struct cpu_hw_sf {TYPE_1__ lsctl; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  hw_perf_event_update (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumsf_pmu_stop(struct perf_event *event, int flags)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	if (event->hw.state & PERF_HES_STOPPED)
		return;

	perf_pmu_disable(event->pmu);
	cpuhw->lsctl.cs = 0;
	cpuhw->lsctl.cd = 0;
	event->hw.state |= PERF_HES_STOPPED;

	if ((flags & PERF_EF_UPDATE) && !(event->hw.state & PERF_HES_UPTODATE)) {
		hw_perf_event_update(event, 1);
		event->hw.state |= PERF_HES_UPTODATE;
	}
	perf_pmu_enable(event->pmu);
}