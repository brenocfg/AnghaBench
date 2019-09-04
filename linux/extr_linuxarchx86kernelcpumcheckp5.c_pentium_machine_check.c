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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  MSR_IA32_P5_MC_ADDR ; 
 int /*<<< orphan*/  MSR_IA32_P5_MC_TYPE ; 
 int /*<<< orphan*/  TAINT_MACHINE_CHECK ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ist_enter (struct pt_regs*) ; 
 int /*<<< orphan*/  ist_exit (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void pentium_machine_check(struct pt_regs *regs, long error_code)
{
	u32 loaddr, hi, lotype;

	ist_enter(regs);

	rdmsr(MSR_IA32_P5_MC_ADDR, loaddr, hi);
	rdmsr(MSR_IA32_P5_MC_TYPE, lotype, hi);

	pr_emerg("CPU#%d: Machine Check Exception:  0x%8X (type 0x%8X).\n",
		 smp_processor_id(), loaddr, lotype);

	if (lotype & (1<<5)) {
		pr_emerg("CPU#%d: Possible thermal failure (CPU on fire ?).\n",
			 smp_processor_id());
	}

	add_taint(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

	ist_exit(regs);
}