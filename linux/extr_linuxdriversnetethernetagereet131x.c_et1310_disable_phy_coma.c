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
struct et131x_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_csr; } ;
struct TYPE_4__ {TYPE_1__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_PMCSR_INIT ; 
 int /*<<< orphan*/  ET_PM_PHY_SW_COMA ; 
 int /*<<< orphan*/  FMP_ADAPTER_LOWER_POWER ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_enable_txrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et1310_disable_phy_coma(struct et131x_adapter *adapter)
{
	u32 pmcsr;

	pmcsr = readl(&adapter->regs->global.pm_csr);

	/* Disable phy_sw_coma register and re-enable JAGCore clocks */
	pmcsr |= ET_PMCSR_INIT;
	pmcsr &= ~ET_PM_PHY_SW_COMA;
	writel(pmcsr, &adapter->regs->global.pm_csr);

	/* Restore the GbE PHY speed and duplex modes;
	 * Reset JAGCore; re-configure and initialize JAGCore and gigE PHY
	 */

	/* Re-initialize the send structures */
	et131x_init_send(adapter);

	/* Bring the device back to the state it was during init prior to
	 * autonegotiation being complete.  This way, when we get the auto-neg
	 * complete interrupt, we can complete init by calling ConfigMacREGS2.
	 */
	et131x_soft_reset(adapter);

	et131x_adapter_setup(adapter);

	/* Allow Tx to restart */
	adapter->flags &= ~FMP_ADAPTER_LOWER_POWER;

	et131x_enable_txrx(adapter->netdev);
}