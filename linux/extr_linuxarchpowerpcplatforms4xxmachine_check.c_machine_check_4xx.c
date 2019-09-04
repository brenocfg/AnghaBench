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
struct pt_regs {unsigned long dsisr; } ;

/* Variables and functions */
 unsigned long ESR_IMCP ; 
 int /*<<< orphan*/  SPRN_ESR ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 

int machine_check_4xx(struct pt_regs *regs)
{
	unsigned long reason = regs->dsisr;

	if (reason & ESR_IMCP) {
		printk("Instruction");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	} else
		printk("Data");
	printk(" machine check in kernel mode.\n");

	return 0;
}