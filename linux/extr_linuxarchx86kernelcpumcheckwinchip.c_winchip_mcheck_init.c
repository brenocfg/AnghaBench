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
typedef  int u32 ;
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IDT_FCR1 ; 
 int /*<<< orphan*/  X86_CR4_MCE ; 
 int /*<<< orphan*/  cr4_set_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_vector ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  winchip_machine_check ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

void winchip_mcheck_init(struct cpuinfo_x86 *c)
{
	u32 lo, hi;

	machine_check_vector = winchip_machine_check;
	/* Make sure the vector pointer is visible before we enable MCEs: */
	wmb();

	rdmsr(MSR_IDT_FCR1, lo, hi);
	lo |= (1<<2);	/* Enable EIERRINT (int 18 MCE) */
	lo &= ~(1<<4);	/* Enable MCE */
	wrmsr(MSR_IDT_FCR1, lo, hi);

	cr4_set_bits(X86_CR4_MCE);

	pr_info("Winchip machine check reporting enabled on CPU#0.\n");
}