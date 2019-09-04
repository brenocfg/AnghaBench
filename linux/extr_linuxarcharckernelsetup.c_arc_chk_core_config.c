#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fpu_dp; int fpu_sp; int /*<<< orphan*/  timer1; int /*<<< orphan*/  timer0; } ;
struct TYPE_3__ {int dsp; } ;
struct cpuinfo_arc {TYPE_2__ extn; TYPE_1__ extn_mpy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARC_FPU_SAVE_RESTORE ; 
 int /*<<< orphan*/  CONFIG_ARC_HAS_ACCL_REGS ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct cpuinfo_arc* cpuinfo_arc700 ; 
 scalar_t__ is_isa_arcompact () ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 size_t smp_processor_id () ; 

__attribute__((used)) static void arc_chk_core_config(void)
{
	struct cpuinfo_arc *cpu = &cpuinfo_arc700[smp_processor_id()];
	int saved = 0, present = 0;
	char *opt_nm = NULL;

	if (!cpu->extn.timer0)
		panic("Timer0 is not present!\n");

	if (!cpu->extn.timer1)
		panic("Timer1 is not present!\n");

#ifdef CONFIG_ARC_HAS_DCCM
	/*
	 * DCCM can be arbit placed in hardware.
	 * Make sure it's placement/sz matches what Linux is built with
	 */
	if ((unsigned int)__arc_dccm_base != cpu->dccm.base_addr)
		panic("Linux built with incorrect DCCM Base address\n");

	if (CONFIG_ARC_DCCM_SZ != cpu->dccm.sz)
		panic("Linux built with incorrect DCCM Size\n");
#endif

#ifdef CONFIG_ARC_HAS_ICCM
	if (CONFIG_ARC_ICCM_SZ != cpu->iccm.sz)
		panic("Linux built with incorrect ICCM Size\n");
#endif

	/*
	 * FP hardware/software config sanity
	 * -If hardware present, kernel needs to save/restore FPU state
	 * -If not, it will crash trying to save/restore the non-existant regs
	 */

	if (is_isa_arcompact()) {
		opt_nm = "CONFIG_ARC_FPU_SAVE_RESTORE";
		saved = IS_ENABLED(CONFIG_ARC_FPU_SAVE_RESTORE);

		/* only DPDP checked since SP has no arch visible regs */
		present = cpu->extn.fpu_dp;
	} else {
		opt_nm = "CONFIG_ARC_HAS_ACCL_REGS";
		saved = IS_ENABLED(CONFIG_ARC_HAS_ACCL_REGS);

		/* Accumulator Low:High pair (r58:59) present if DSP MPY or FPU */
		present = cpu->extn_mpy.dsp | cpu->extn.fpu_sp | cpu->extn.fpu_dp;
	}

	if (present && !saved)
		pr_warn("Enable %s for working apps\n", opt_nm);
	else if (!present && saved)
		panic("Disable %s, hardware NOT present\n", opt_nm);
}