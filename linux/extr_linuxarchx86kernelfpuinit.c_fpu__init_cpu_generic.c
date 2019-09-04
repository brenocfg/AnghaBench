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
 unsigned long X86_CR0_EM ; 
 unsigned long X86_CR0_TS ; 
 unsigned long X86_CR4_OSFXSR ; 
 unsigned long X86_CR4_OSXMMEXCPT ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  X86_FEATURE_FXSR ; 
 int /*<<< orphan*/  X86_FEATURE_XMM ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr4_set_bits (unsigned long) ; 
 unsigned long read_cr0 () ; 
 int /*<<< orphan*/  write_cr0 (unsigned long) ; 

__attribute__((used)) static void fpu__init_cpu_generic(void)
{
	unsigned long cr0;
	unsigned long cr4_mask = 0;

	if (boot_cpu_has(X86_FEATURE_FXSR))
		cr4_mask |= X86_CR4_OSFXSR;
	if (boot_cpu_has(X86_FEATURE_XMM))
		cr4_mask |= X86_CR4_OSXMMEXCPT;
	if (cr4_mask)
		cr4_set_bits(cr4_mask);

	cr0 = read_cr0();
	cr0 &= ~(X86_CR0_TS|X86_CR0_EM); /* clear TS and EM */
	if (!boot_cpu_has(X86_FEATURE_FPU))
		cr0 |= X86_CR0_EM;
	write_cr0(cr0);

	/* Flush out any pending x87 state: */
#ifdef CONFIG_MATH_EMULATION
	if (!boot_cpu_has(X86_FEATURE_FPU))
		fpstate_init_soft(&current->thread.fpu.state.soft);
	else
#endif
		asm volatile ("fninit");
}