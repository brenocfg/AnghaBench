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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */

int detect_extended_topology_early(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	unsigned int eax, ebx, ecx, edx;

	if (c->cpuid_level < 0xb)
		return -1;

	cpuid_count(0xb, SMT_LEVEL, &eax, &ebx, &ecx, &edx);

	/*
	 * check if the cpuid leaf 0xb is actually implemented.
	 */
	if (ebx == 0 || (LEAFB_SUBTYPE(ecx) != SMT_TYPE))
		return -1;

	set_cpu_cap(c, X86_FEATURE_XTOPOLOGY);

	/*
	 * initial apic id, which also represents 32-bit extended x2apic id.
	 */
	c->initial_apicid = edx;
	smp_num_siblings = LEVEL_MAX_SIBLINGS(ebx);
#endif
	return 0;
}