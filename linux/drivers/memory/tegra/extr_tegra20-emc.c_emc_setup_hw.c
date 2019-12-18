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
typedef  int u32 ;
struct tegra_emc {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EMC_CFG_2 ; 
 int EMC_CLKCHANGE_COMPLETE_INT ; 
 int EMC_CLKCHANGE_PD_ENABLE ; 
 int EMC_CLKCHANGE_REQ_ENABLE ; 
 int EMC_CLKCHANGE_SR_ENABLE ; 
 scalar_t__ EMC_INTMASK ; 
 scalar_t__ EMC_INTSTATUS ; 
 int EMC_REFRESH_OVERFLOW_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int emc_setup_hw(struct tegra_emc *emc)
{
	u32 intmask = EMC_REFRESH_OVERFLOW_INT | EMC_CLKCHANGE_COMPLETE_INT;
	u32 emc_cfg;

	emc_cfg = readl_relaxed(emc->regs + EMC_CFG_2);

	/*
	 * Depending on a memory type, DRAM should enter either self-refresh
	 * or power-down state on EMC clock change.
	 */
	if (!(emc_cfg & EMC_CLKCHANGE_PD_ENABLE) &&
	    !(emc_cfg & EMC_CLKCHANGE_SR_ENABLE)) {
		dev_err(emc->dev,
			"bootloader didn't specify DRAM auto-suspend mode\n");
		return -EINVAL;
	}

	/* enable EMC and CAR to handshake on PLL divider/source changes */
	emc_cfg |= EMC_CLKCHANGE_REQ_ENABLE;
	writel_relaxed(emc_cfg, emc->regs + EMC_CFG_2);

	/* initialize interrupt */
	writel_relaxed(intmask, emc->regs + EMC_INTMASK);
	writel_relaxed(intmask, emc->regs + EMC_INTSTATUS);

	return 0;
}