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
typedef  int u32 ;

/* Variables and functions */
 int DC_DISABLE ; 
 int /*<<< orphan*/  MSR_IA32_THERM_CONTROL ; 
 int /*<<< orphan*/  rdmsr_on_cpu (unsigned int,int /*<<< orphan*/ ,int*,int*) ; 
 int stock_freq ; 

__attribute__((used)) static unsigned int cpufreq_p4_get(unsigned int cpu)
{
	u32 l, h;

	rdmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, &l, &h);

	if (l & 0x10) {
		l = l >> 1;
		l &= 0x7;
	} else
		l = DC_DISABLE;

	if (l != DC_DISABLE)
		return stock_freq * l / 8;

	return stock_freq;
}