#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct npe {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_data; int /*<<< orphan*/  exec_status_cmd; int /*<<< orphan*/  exec_addr; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 npe_cmd_read(struct npe *npe, u32 addr, int cmd)
{
	__raw_writel(addr, &npe->regs->exec_addr);
	__raw_writel(cmd, &npe->regs->exec_status_cmd);
	/* Iintroduce extra read cycles after issuing read command to NPE
	   so that we read the register after the NPE has updated it.
	   This is to overcome race condition between XScale and NPE */
	__raw_readl(&npe->regs->exec_data);
	__raw_readl(&npe->regs->exec_data);
	return __raw_readl(&npe->regs->exec_data);
}