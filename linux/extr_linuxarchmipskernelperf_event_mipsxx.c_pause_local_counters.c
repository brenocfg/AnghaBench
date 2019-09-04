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
struct cpu_hw_events {int* saved_ctrl; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int M_PERFCTL_COUNT_EVENT_WHENEVER ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ mipspmu ; 
 int mipsxx_pmu_read_control (int) ; 
 int /*<<< orphan*/  mipsxx_pmu_write_control (int,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pause_local_counters(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int ctr = mipspmu.num_counters;
	unsigned long flags;

	local_irq_save(flags);
	do {
		ctr--;
		cpuc->saved_ctrl[ctr] = mipsxx_pmu_read_control(ctr);
		mipsxx_pmu_write_control(ctr, cpuc->saved_ctrl[ctr] &
					 ~M_PERFCTL_COUNT_EVENT_WHENEVER);
	} while (ctr > 0);
	local_irq_restore(flags);
}