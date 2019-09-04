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

__attribute__((used)) static void dump_207_sprs(void)
{
#ifdef CONFIG_PPC64
	unsigned long msr;

	if (!cpu_has_feature(CPU_FTR_ARCH_207S))
		return;

	printf("dpdes  = %.16lx  tir   = %.16lx cir    = %.8lx\n",
		mfspr(SPRN_DPDES), mfspr(SPRN_TIR), mfspr(SPRN_CIR));

	printf("fscr   = %.16lx  tar   = %.16lx pspb   = %.8lx\n",
		mfspr(SPRN_FSCR), mfspr(SPRN_TAR), mfspr(SPRN_PSPB));

	msr = mfmsr();
	if (msr & MSR_TM) {
		/* Only if TM has been enabled in the kernel */
		printf("tfhar  = %.16lx  tfiar = %.16lx texasr = %.16lx\n",
			mfspr(SPRN_TFHAR), mfspr(SPRN_TFIAR),
			mfspr(SPRN_TEXASR));
	}

	printf("mmcr0  = %.16lx  mmcr1 = %.16lx mmcr2  = %.16lx\n",
		mfspr(SPRN_MMCR0), mfspr(SPRN_MMCR1), mfspr(SPRN_MMCR2));
	printf("pmc1   = %.8lx pmc2 = %.8lx  pmc3 = %.8lx  pmc4   = %.8lx\n",
		mfspr(SPRN_PMC1), mfspr(SPRN_PMC2),
		mfspr(SPRN_PMC3), mfspr(SPRN_PMC4));
	printf("mmcra  = %.16lx   siar = %.16lx pmc5   = %.8lx\n",
		mfspr(SPRN_MMCRA), mfspr(SPRN_SIAR), mfspr(SPRN_PMC5));
	printf("sdar   = %.16lx   sier = %.16lx pmc6   = %.8lx\n",
		mfspr(SPRN_SDAR), mfspr(SPRN_SIER), mfspr(SPRN_PMC6));
	printf("ebbhr  = %.16lx  ebbrr = %.16lx bescr  = %.16lx\n",
		mfspr(SPRN_EBBHR), mfspr(SPRN_EBBRR), mfspr(SPRN_BESCR));
	printf("iamr   = %.16lx\n", mfspr(SPRN_IAMR));

	if (!(msr & MSR_HV))
		return;

	printf("hfscr  = %.16lx  dhdes = %.16lx rpr    = %.16lx\n",
		mfspr(SPRN_HFSCR), mfspr(SPRN_DHDES), mfspr(SPRN_RPR));
	printf("dawr   = %.16lx  dawrx = %.16lx ciabr  = %.16lx\n",
		mfspr(SPRN_DAWR), mfspr(SPRN_DAWRX), mfspr(SPRN_CIABR));
#endif
}