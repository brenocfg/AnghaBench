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
struct tegra_pcie_soc {scalar_t__ update_clamp_threshold; } ;
struct tegra_pcie_port {scalar_t__ base; TYPE_1__* pcie; } ;
struct TYPE_2__ {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 scalar_t__ RP_PRIV_MISC ; 
 int RP_PRIV_MISC_CTLR_CLK_CLAMP_ENABLE ; 
 int RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD ; 
 int RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD_MASK ; 
 int RP_PRIV_MISC_TMS_CLK_CLAMP_ENABLE ; 
 int RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD ; 
 int RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD_MASK ; 
 scalar_t__ RP_VEND_CTL1 ; 
 int RP_VEND_CTL1_ERPT ; 
 scalar_t__ RP_VEND_XP ; 
 scalar_t__ RP_VEND_XP_BIST ; 
 int RP_VEND_XP_BIST_GOTO_L1_L2_AFTER_DLLP_DONE ; 
 int RP_VEND_XP_OPPORTUNISTIC_ACK ; 
 int RP_VEND_XP_OPPORTUNISTIC_UPDATEFC ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_pcie_enable_rp_features(struct tegra_pcie_port *port)
{
	const struct tegra_pcie_soc *soc = port->pcie->soc;
	u32 value;

	/* Enable AER capability */
	value = readl(port->base + RP_VEND_CTL1);
	value |= RP_VEND_CTL1_ERPT;
	writel(value, port->base + RP_VEND_CTL1);

	/* Optimal settings to enhance bandwidth */
	value = readl(port->base + RP_VEND_XP);
	value |= RP_VEND_XP_OPPORTUNISTIC_ACK;
	value |= RP_VEND_XP_OPPORTUNISTIC_UPDATEFC;
	writel(value, port->base + RP_VEND_XP);

	/*
	 * LTSSM will wait for DLLP to finish before entering L1 or L2,
	 * to avoid truncation of PM messages which results in receiver errors
	 */
	value = readl(port->base + RP_VEND_XP_BIST);
	value |= RP_VEND_XP_BIST_GOTO_L1_L2_AFTER_DLLP_DONE;
	writel(value, port->base + RP_VEND_XP_BIST);

	value = readl(port->base + RP_PRIV_MISC);
	value |= RP_PRIV_MISC_CTLR_CLK_CLAMP_ENABLE;
	value |= RP_PRIV_MISC_TMS_CLK_CLAMP_ENABLE;

	if (soc->update_clamp_threshold) {
		value &= ~(RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD_MASK |
				RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD_MASK);
		value |= RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD |
			RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD;
	}

	writel(value, port->base + RP_PRIV_MISC);
}