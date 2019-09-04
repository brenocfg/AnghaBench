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
struct cpuinfo_mips {unsigned int globalnumber; } ;

/* Variables and functions */
 unsigned int MIPS_GLOBALNUMBER_CORE ; 
 unsigned int MIPS_GLOBALNUMBER_CORE_SHF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void cpu_set_core(struct cpuinfo_mips *cpuinfo, unsigned int core)
{
	/* Ensure the core number fits in the field */
	WARN_ON(core > (MIPS_GLOBALNUMBER_CORE >> MIPS_GLOBALNUMBER_CORE_SHF));

	cpuinfo->globalnumber &= ~MIPS_GLOBALNUMBER_CORE;
	cpuinfo->globalnumber |= core << MIPS_GLOBALNUMBER_CORE_SHF;
}