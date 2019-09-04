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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int tstate; scalar_t__ tpc; } ;

/* Variables and functions */
 int TSTATE_PRIV ; 
 int /*<<< orphan*/  compute_effective_address (struct pt_regs*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4v_report_real_raddr(const char *pfx, struct pt_regs *regs)
{
	unsigned int insn;
	u64 addr;

	if (!(regs->tstate & TSTATE_PRIV))
		return;

	insn = *(unsigned int *) regs->tpc;

	addr = compute_effective_address(regs, insn, 0);

	printk("%s: insn effective address [0x%016llx]\n",
	       pfx, addr);
}