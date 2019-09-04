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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_set_elr (struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  pt_set_rte_sp (struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  pt_set_usermode (struct pt_regs*) ; 

void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long sp)
{
	/* We want to zero all data-containing registers. Is this overkill? */
	memset(regs, 0, sizeof(*regs));
	/* We might want to also zero all Processor registers here */
	pt_set_usermode(regs);
	pt_set_elr(regs, pc);
	pt_set_rte_sp(regs, sp);
}