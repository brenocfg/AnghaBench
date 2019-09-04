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
struct cpuinfo_x86 {int cpuid_level; int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_ARCH_PERFMON ; 
 int /*<<< orphan*/  X86_FEATURE_VMX ; 
 int /*<<< orphan*/  centaur_detect_vmx_virtcap (struct cpuinfo_x86*) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 unsigned int cpuid_eax (int) ; 
 int /*<<< orphan*/  detect_num_cpu_cores (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  early_init_centaur (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_c3 (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  init_intel_cacheinfo (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_centaur(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	char *name;
	u32  fcr_set = 0;
	u32  fcr_clr = 0;
	u32  lo, hi, newlo;
	u32  aa, bb, cc, dd;

	/*
	 * Bit 31 in normal CPUID used for nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);
#endif
	early_init_centaur(c);
	init_intel_cacheinfo(c);
	detect_num_cpu_cores(c);
#ifdef CONFIG_X86_32
	detect_ht(c);
#endif

	if (c->cpuid_level > 9) {
		unsigned int eax = cpuid_eax(10);

		/*
		 * Check for version and the number of counters
		 * Version(eax[7:0]) can't be 0;
		 * Counters(eax[15:8]) should be greater than 1;
		 */
		if ((eax & 0xff) && (((eax >> 8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATURE_ARCH_PERFMON);
	}

	switch (c->x86) {
#ifdef CONFIG_X86_32
	case 5:
		switch (c->x86_model) {
		case 4:
			name = "C6";
			fcr_set = ECX8|DSMC|EDCTLB|EMMX|ERETSTK;
			fcr_clr = DPDC;
			pr_notice("Disabling bugged TSC.\n");
			clear_cpu_cap(c, X86_FEATURE_TSC);
			break;
		case 8:
			switch (c->x86_stepping) {
			default:
			name = "2";
				break;
			case 7 ... 9:
				name = "2A";
				break;
			case 10 ... 15:
				name = "2B";
				break;
			}
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			break;
		case 9:
			name = "3";
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			break;
		default:
			name = "??";
		}

		rdmsr(MSR_IDT_FCR1, lo, hi);
		newlo = (lo|fcr_set) & (~fcr_clr);

		if (newlo != lo) {
			pr_info("Centaur FCR was 0x%X now 0x%X\n",
				lo, newlo);
			wrmsr(MSR_IDT_FCR1, newlo, hi);
		} else {
			pr_info("Centaur FCR is 0x%X\n", lo);
		}
		/* Emulate MTRRs using Centaur's MCR. */
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
		/* Report CX8 */
		set_cpu_cap(c, X86_FEATURE_CX8);
		/* Set 3DNow! on Winchip 2 and above. */
		if (c->x86_model >= 8)
			set_cpu_cap(c, X86_FEATURE_3DNOW);
		/* See if we can find out some more. */
		if (cpuid_eax(0x80000000) >= 0x80000005) {
			/* Yes, we can. */
			cpuid(0x80000005, &aa, &bb, &cc, &dd);
			/* Add L1 data and code cache sizes. */
			c->x86_cache_size = (cc>>24)+(dd>>24);
		}
		sprintf(c->x86_model_id, "WinChip %s", name);
		break;
#endif
	case 6:
		init_c3(c);
		break;
	}
#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
#endif

	if (cpu_has(c, X86_FEATURE_VMX))
		centaur_detect_vmx_virtcap(c);
}