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
typedef  int u64 ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_INT ; 
 int ARCH_PERFMON_EVENTSEL_OS ; 
 int ARCH_PERFMON_EVENTSEL_USR ; 
 unsigned long DEBUGCTLMSR_BTINT ; 
 unsigned long DEBUGCTLMSR_BTS ; 
 unsigned long DEBUGCTLMSR_BTS_OFF_OS ; 
 unsigned long DEBUGCTLMSR_BTS_OFF_USR ; 
 unsigned long DEBUGCTLMSR_TR ; 
 unsigned long get_debugctlmsr () ; 
 int /*<<< orphan*/  update_debugctlmsr (unsigned long) ; 

void intel_pmu_enable_bts(u64 config)
{
	unsigned long debugctlmsr;

	debugctlmsr = get_debugctlmsr();

	debugctlmsr |= DEBUGCTLMSR_TR;
	debugctlmsr |= DEBUGCTLMSR_BTS;
	if (config & ARCH_PERFMON_EVENTSEL_INT)
		debugctlmsr |= DEBUGCTLMSR_BTINT;

	if (!(config & ARCH_PERFMON_EVENTSEL_OS))
		debugctlmsr |= DEBUGCTLMSR_BTS_OFF_OS;

	if (!(config & ARCH_PERFMON_EVENTSEL_USR))
		debugctlmsr |= DEBUGCTLMSR_BTS_OFF_USR;

	update_debugctlmsr(debugctlmsr);
}