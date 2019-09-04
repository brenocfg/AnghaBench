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
struct TYPE_2__ {int /*<<< orphan*/  alt_ll_halt; int /*<<< orphan*/  ll_halt; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FW_INIT_HALT_P ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_ct_notify_fail(struct bfa_ioc *ioc)
{
	writel(__FW_INIT_HALT_P, ioc->ioc_regs.ll_halt);
	writel(__FW_INIT_HALT_P, ioc->ioc_regs.alt_ll_halt);
	/* Wait for halt to take effect */
	readl(ioc->ioc_regs.ll_halt);
	readl(ioc->ioc_regs.alt_ll_halt);
}