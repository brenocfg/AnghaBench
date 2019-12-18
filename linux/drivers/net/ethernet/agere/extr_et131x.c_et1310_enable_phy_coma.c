#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct et131x_adapter {TYPE_2__* regs; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_csr; } ;
struct TYPE_4__ {TYPE_1__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_PMCSR_INIT ; 
 int /*<<< orphan*/  ET_PM_PHY_SW_COMA ; 
 int /*<<< orphan*/  FMP_ADAPTER_LOWER_POWER ; 
 int /*<<< orphan*/  et131x_disable_txrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et1310_enable_phy_coma(struct et131x_adapter *adapter)
{
	u32 pmcsr = readl(&adapter->regs->global.pm_csr);

	/* Stop sending packets. */
	adapter->flags |= FMP_ADAPTER_LOWER_POWER;

	/* Wait for outstanding Receive packets */
	et131x_disable_txrx(adapter->netdev);

	/* Gate off JAGCore 3 clock domains */
	pmcsr &= ~ET_PMCSR_INIT;
	writel(pmcsr, &adapter->regs->global.pm_csr);

	/* Program gigE PHY in to Coma mode */
	pmcsr |= ET_PM_PHY_SW_COMA;
	writel(pmcsr, &adapter->regs->global.pm_csr);
}