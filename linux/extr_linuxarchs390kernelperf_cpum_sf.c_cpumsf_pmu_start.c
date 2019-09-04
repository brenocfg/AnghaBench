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
struct TYPE_3__ {int cs; int cd; } ;
struct cpu_hw_sf {TYPE_1__ lsctl; } ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ SAMPL_DIAG_MODE (TYPE_2__*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumsf_pmu_start(struct perf_event *event, int flags)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	perf_pmu_disable(event->pmu);
	event->hw.state = 0;
	cpuhw->lsctl.cs = 1;
	if (SAMPL_DIAG_MODE(&event->hw))
		cpuhw->lsctl.cd = 1;
	perf_pmu_enable(event->pmu);
}