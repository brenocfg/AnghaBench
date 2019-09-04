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
struct et131x_adapter {TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmc_ctrl; } ;
struct TYPE_4__ {TYPE_1__ mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_MMC_ENABLE ; 
 int /*<<< orphan*/  et1310_config_mac_regs1 (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_config_macstat_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_config_rxmac_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_config_txmac_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_phy_power_switch (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et131x_config_rx_dma_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_config_tx_dma_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_configure_global_regs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_xcvr_init (struct et131x_adapter*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_adapter_setup(struct et131x_adapter *adapter)
{
	et131x_configure_global_regs(adapter);
	et1310_config_mac_regs1(adapter);

	/* Configure the MMC registers */
	/* All we need to do is initialize the Memory Control Register */
	writel(ET_MMC_ENABLE, &adapter->regs->mmc.mmc_ctrl);

	et1310_config_rxmac_regs(adapter);
	et1310_config_txmac_regs(adapter);

	et131x_config_rx_dma_regs(adapter);
	et131x_config_tx_dma_regs(adapter);

	et1310_config_macstat_regs(adapter);

	et1310_phy_power_switch(adapter, 0);
	et131x_xcvr_init(adapter);
}