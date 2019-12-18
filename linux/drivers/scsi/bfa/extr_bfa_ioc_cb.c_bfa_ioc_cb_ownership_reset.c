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
struct TYPE_2__ {int /*<<< orphan*/  ioc_sem_reg; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_cb_ownership_reset(struct bfa_ioc_s *ioc)
{

	/*
	 * Read the hw sem reg to make sure that it is locked
	 * before we clear it. If it is not locked, writing 1
	 * will lock it instead of clearing it.
	 */
	readl(ioc->ioc_regs.ioc_sem_reg);
	writel(1, ioc->ioc_regs.ioc_sem_reg);
}