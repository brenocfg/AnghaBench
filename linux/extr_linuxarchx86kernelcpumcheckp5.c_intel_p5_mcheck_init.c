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
typedef  int /*<<< orphan*/  u32 ;
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_P5_MC_ADDR ; 
 int /*<<< orphan*/  MSR_IA32_P5_MC_TYPE ; 
 int /*<<< orphan*/  X86_CR4_MCE ; 
 int /*<<< orphan*/  X86_FEATURE_MCE ; 
 int /*<<< orphan*/  cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr4_set_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_vector ; 
 int /*<<< orphan*/  mce_p5_enabled ; 
 int /*<<< orphan*/  pentium_machine_check ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  wmb () ; 

void intel_p5_mcheck_init(struct cpuinfo_x86 *c)
{
	u32 l, h;

	/* Default P5 to off as its often misconnected: */
	if (!mce_p5_enabled)
		return;

	/* Check for MCE support: */
	if (!cpu_has(c, X86_FEATURE_MCE))
		return;

	machine_check_vector = pentium_machine_check;
	/* Make sure the vector pointer is visible before we enable MCEs: */
	wmb();

	/* Read registers before enabling: */
	rdmsr(MSR_IA32_P5_MC_ADDR, l, h);
	rdmsr(MSR_IA32_P5_MC_TYPE, l, h);
	pr_info("Intel old style machine check architecture supported.\n");

	/* Enable MCE: */
	cr4_set_bits(X86_CR4_MCE);
	pr_info("Intel old style machine check reporting enabled on CPU#%d.\n",
		smp_processor_id());
}