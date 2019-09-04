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

__attribute__((used)) static void dump_206_sprs(void)
{
#ifdef CONFIG_PPC64
	if (!cpu_has_feature(CPU_FTR_ARCH_206))
		return;

	/* Actually some of these pre-date 2.06, but whatevs */

	printf("srr0   = %.16lx  srr1  = %.16lx dsisr  = %.8lx\n",
		mfspr(SPRN_SRR0), mfspr(SPRN_SRR1), mfspr(SPRN_DSISR));
	printf("dscr   = %.16lx  ppr   = %.16lx pir    = %.8lx\n",
		mfspr(SPRN_DSCR), mfspr(SPRN_PPR), mfspr(SPRN_PIR));
	printf("amr    = %.16lx  uamor = %.16lx\n",
		mfspr(SPRN_AMR), mfspr(SPRN_UAMOR));

	if (!(mfmsr() & MSR_HV))
		return;

	printf("sdr1   = %.16lx  hdar  = %.16lx hdsisr = %.8lx\n",
		mfspr(SPRN_SDR1), mfspr(SPRN_HDAR), mfspr(SPRN_HDSISR));
	printf("hsrr0  = %.16lx hsrr1  = %.16lx hdec   = %.16lx\n",
		mfspr(SPRN_HSRR0), mfspr(SPRN_HSRR1), mfspr(SPRN_HDEC));
	printf("lpcr   = %.16lx  pcr   = %.16lx lpidr  = %.8lx\n",
		mfspr(SPRN_LPCR), mfspr(SPRN_PCR), mfspr(SPRN_LPID));
	printf("hsprg0 = %.16lx hsprg1 = %.16lx amor   = %.16lx\n",
		mfspr(SPRN_HSPRG0), mfspr(SPRN_HSPRG1), mfspr(SPRN_AMOR));
	printf("dabr   = %.16lx dabrx  = %.16lx\n",
		mfspr(SPRN_DABR), mfspr(SPRN_DABRX));
#endif
}