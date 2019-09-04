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
typedef  int u16 ;

/* Variables and functions */
 unsigned long X86_CR0_EM ; 
 unsigned long X86_CR0_TS ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 unsigned long read_cr0 () ; 
 int /*<<< orphan*/  write_cr0 (unsigned long) ; 

__attribute__((used)) static bool fpu__probe_without_cpuid(void)
{
	unsigned long cr0;
	u16 fsw, fcw;

	fsw = fcw = 0xffff;

	cr0 = read_cr0();
	cr0 &= ~(X86_CR0_TS | X86_CR0_EM);
	write_cr0(cr0);

	asm volatile("fninit ; fnstsw %0 ; fnstcw %1" : "+m" (fsw), "+m" (fcw));

	pr_info("x86/fpu: Probing for FPU: FSW=0x%04hx FCW=0x%04hx\n", fsw, fcw);

	return fsw == 0 && (fcw & 0x103f) == 0x003f;
}