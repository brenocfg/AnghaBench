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
struct cpu_hw_events {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 unsigned long DEBUGCTLMSR_BTINT ; 
 unsigned long DEBUGCTLMSR_BTS ; 
 unsigned long DEBUGCTLMSR_BTS_OFF_OS ; 
 unsigned long DEBUGCTLMSR_BTS_OFF_USR ; 
 unsigned long DEBUGCTLMSR_TR ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 unsigned long get_debugctlmsr () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_debugctlmsr (unsigned long) ; 

void intel_pmu_disable_bts(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	unsigned long debugctlmsr;

	if (!cpuc->ds)
		return;

	debugctlmsr = get_debugctlmsr();

	debugctlmsr &=
		~(DEBUGCTLMSR_TR | DEBUGCTLMSR_BTS | DEBUGCTLMSR_BTINT |
		  DEBUGCTLMSR_BTS_OFF_OS | DEBUGCTLMSR_BTS_OFF_USR);

	update_debugctlmsr(debugctlmsr);
}