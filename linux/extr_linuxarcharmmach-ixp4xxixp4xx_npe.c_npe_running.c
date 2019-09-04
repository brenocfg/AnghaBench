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
struct npe {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_status_cmd; } ;

/* Variables and functions */
 int STAT_RUN ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 

int npe_running(struct npe *npe)
{
	return (__raw_readl(&npe->regs->exec_status_cmd) & STAT_RUN) != 0;
}