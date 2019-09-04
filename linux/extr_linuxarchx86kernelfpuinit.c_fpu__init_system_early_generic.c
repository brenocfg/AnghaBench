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
 int /*<<< orphan*/  X86_FEATURE_CPUID ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  boot_cpu_data ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_caps_cleared ; 
 scalar_t__ fpu__probe_without_cpuid () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  setup_clear_cpu_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_force_cpu_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  test_cpu_cap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpu__init_system_early_generic(struct cpuinfo_x86 *c)
{
	if (!boot_cpu_has(X86_FEATURE_CPUID) &&
	    !test_bit(X86_FEATURE_FPU, (unsigned long *)cpu_caps_cleared)) {
		if (fpu__probe_without_cpuid())
			setup_force_cpu_cap(X86_FEATURE_FPU);
		else
			setup_clear_cpu_cap(X86_FEATURE_FPU);
	}

#ifndef CONFIG_MATH_EMULATION
	if (!test_cpu_cap(&boot_cpu_data, X86_FEATURE_FPU)) {
		pr_emerg("x86/fpu: Giving up, no FPU found and no math emulation present\n");
		for (;;)
			asm volatile("hlt");
	}
#endif
}