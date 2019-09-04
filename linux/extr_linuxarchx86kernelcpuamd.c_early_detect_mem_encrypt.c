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
struct cpuinfo_x86 {int x86_phys_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_32 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_K7_HWCR ; 
 int MSR_K7_HWCR_SMMLOCK ; 
 int /*<<< orphan*/  MSR_K8_SYSCFG ; 
 int MSR_K8_SYSCFG_MEM_ENCRYPT ; 
 int /*<<< orphan*/  X86_FEATURE_SEV ; 
 int /*<<< orphan*/  X86_FEATURE_SME ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int cpuid_ebx (int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void early_detect_mem_encrypt(struct cpuinfo_x86 *c)
{
	u64 msr;

	/*
	 * BIOS support is required for SME and SEV.
	 *   For SME: If BIOS has enabled SME then adjust x86_phys_bits by
	 *	      the SME physical address space reduction value.
	 *	      If BIOS has not enabled SME then don't advertise the
	 *	      SME feature (set in scattered.c).
	 *   For SEV: If BIOS has not enabled SEV then don't advertise the
	 *            SEV feature (set in scattered.c).
	 *
	 *   In all cases, since support for SME and SEV requires long mode,
	 *   don't advertise the feature under CONFIG_X86_32.
	 */
	if (cpu_has(c, X86_FEATURE_SME) || cpu_has(c, X86_FEATURE_SEV)) {
		/* Check if memory encryption is enabled */
		rdmsrl(MSR_K8_SYSCFG, msr);
		if (!(msr & MSR_K8_SYSCFG_MEM_ENCRYPT))
			goto clear_all;

		/*
		 * Always adjust physical address bits. Even though this
		 * will be a value above 32-bits this is still done for
		 * CONFIG_X86_32 so that accurate values are reported.
		 */
		c->x86_phys_bits -= (cpuid_ebx(0x8000001f) >> 6) & 0x3f;

		if (IS_ENABLED(CONFIG_X86_32))
			goto clear_all;

		rdmsrl(MSR_K7_HWCR, msr);
		if (!(msr & MSR_K7_HWCR_SMMLOCK))
			goto clear_sev;

		return;

clear_all:
		clear_cpu_cap(c, X86_FEATURE_SME);
clear_sev:
		clear_cpu_cap(c, X86_FEATURE_SEV);
	}
}