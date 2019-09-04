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

/* Variables and functions */

__attribute__((used)) static void dump_300_sprs(void)
{
#ifdef CONFIG_PPC64
	bool hv = mfmsr() & MSR_HV;

	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		return;

	printf("pidr   = %.16lx  tidr  = %.16lx\n",
		mfspr(SPRN_PID), mfspr(SPRN_TIDR));
	printf("asdr   = %.16lx  psscr = %.16lx\n",
		mfspr(SPRN_ASDR), hv ? mfspr(SPRN_PSSCR)
					: mfspr(SPRN_PSSCR_PR));

	if (!hv)
		return;

	printf("ptcr   = %.16lx\n",
		mfspr(SPRN_PTCR));
#endif
}