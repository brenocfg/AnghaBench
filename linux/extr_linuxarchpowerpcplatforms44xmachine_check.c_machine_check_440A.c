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
struct pt_regs {unsigned long dsisr; } ;

/* Variables and functions */
 unsigned long ESR_IMCP ; 
 int MCSR_DCFP ; 
 int MCSR_DCSP ; 
 int MCSR_DRB ; 
 int MCSR_DWB ; 
 int MCSR_IB ; 
 int MCSR_ICP ; 
 int MCSR_IMPE ; 
 int MCSR_TLBP ; 
 int /*<<< orphan*/  SPRN_ESR ; 
 int /*<<< orphan*/  SPRN_MCSR ; 
 int /*<<< orphan*/  flush_instruction_cache () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int machine_check_440A(struct pt_regs *regs)
{
	unsigned long reason = regs->dsisr;

	printk("Machine check in kernel mode.\n");
	if (reason & ESR_IMCP){
		printk("Instruction Synchronous Machine Check exception\n");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	}
	else {
		u32 mcsr = mfspr(SPRN_MCSR);
		if (mcsr & MCSR_IB)
			printk("Instruction Read PLB Error\n");
		if (mcsr & MCSR_DRB)
			printk("Data Read PLB Error\n");
		if (mcsr & MCSR_DWB)
			printk("Data Write PLB Error\n");
		if (mcsr & MCSR_TLBP)
			printk("TLB Parity Error\n");
		if (mcsr & MCSR_ICP){
			flush_instruction_cache();
			printk("I-Cache Parity Error\n");
		}
		if (mcsr & MCSR_DCSP)
			printk("D-Cache Search Parity Error\n");
		if (mcsr & MCSR_DCFP)
			printk("D-Cache Flush Parity Error\n");
		if (mcsr & MCSR_IMPE)
			printk("Machine Check exception is imprecise\n");

		/* Clear MCSR */
		mtspr(SPRN_MCSR, mcsr);
	}
	return 0;
}