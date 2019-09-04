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
 int /*<<< orphan*/  CONFIG_CPU_MIPSR6 ; 
 int /*<<< orphan*/  CONFIG_MIPS_MT_SMP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int MIPS_GLOBALNUMBER_VP ; 
 unsigned int MIPS_GLOBALNUMBER_VP_SHF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void cpu_set_vpe_id(struct cpuinfo_mips *cpuinfo, unsigned int vpe)
{
	/* Ensure the VP(E) ID fits in the field */
	WARN_ON(vpe > (MIPS_GLOBALNUMBER_VP >> MIPS_GLOBALNUMBER_VP_SHF));

	/* Ensure we're not using VP(E)s without support */
	WARN_ON(vpe && !IS_ENABLED(CONFIG_MIPS_MT_SMP) &&
		!IS_ENABLED(CONFIG_CPU_MIPSR6));

	cpuinfo->globalnumber &= ~MIPS_GLOBALNUMBER_VP;
	cpuinfo->globalnumber |= vpe << MIPS_GLOBALNUMBER_VP_SHF;
}