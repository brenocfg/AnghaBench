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
struct tegra_sor {TYPE_2__* soc; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_safe; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pll2; int /*<<< orphan*/  pll0; int /*<<< orphan*/  dp_padctl0; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long SOR_DP_PADCTL_PD_TXD_0 ; 
 unsigned long SOR_DP_PADCTL_PD_TXD_1 ; 
 unsigned long SOR_DP_PADCTL_PD_TXD_2 ; 
 unsigned long SOR_DP_PADCTL_PD_TXD_3 ; 
 int /*<<< orphan*/  SOR_LANE_SEQ_CTL ; 
 unsigned long SOR_LANE_SEQ_CTL_POWER_STATE_DOWN ; 
 unsigned long SOR_LANE_SEQ_CTL_SEQUENCE_UP ; 
 unsigned long SOR_LANE_SEQ_CTL_TRIGGER ; 
 unsigned long SOR_PLL0_PWR ; 
 unsigned long SOR_PLL0_VCOPD ; 
 unsigned long SOR_PLL2_PORT_POWERDOWN ; 
 unsigned long SOR_PLL2_SEQ_PLLCAPPD ; 
 unsigned long SOR_PLL2_SEQ_PLLCAPPD_ENFORCE ; 
 int /*<<< orphan*/  SOR_PWR ; 
 unsigned long SOR_PWR_NORMAL_STATE_PU ; 
 unsigned long SOR_PWR_TRIGGER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned long tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int tegra_sor_set_parent_clock (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_sor_power_down(struct tegra_sor *sor)
{
	unsigned long value, timeout;
	int err;

	value = tegra_sor_readl(sor, SOR_PWR);
	value &= ~SOR_PWR_NORMAL_STATE_PU;
	value |= SOR_PWR_TRIGGER;
	tegra_sor_writel(sor, value, SOR_PWR);

	timeout = jiffies + msecs_to_jiffies(250);

	while (time_before(jiffies, timeout)) {
		value = tegra_sor_readl(sor, SOR_PWR);
		if ((value & SOR_PWR_TRIGGER) == 0)
			return 0;

		usleep_range(25, 100);
	}

	if ((value & SOR_PWR_TRIGGER) != 0)
		return -ETIMEDOUT;

	/* switch to safe parent clock */
	err = tegra_sor_set_parent_clock(sor, sor->clk_safe);
	if (err < 0) {
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);
		return err;
	}

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value &= ~(SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_0 |
		   SOR_DP_PADCTL_PD_TXD_1 | SOR_DP_PADCTL_PD_TXD_2);
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	/* stop lane sequencer */
	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_UP |
		SOR_LANE_SEQ_CTL_POWER_STATE_DOWN;
	tegra_sor_writel(sor, value, SOR_LANE_SEQ_CTL);

	timeout = jiffies + msecs_to_jiffies(250);

	while (time_before(jiffies, timeout)) {
		value = tegra_sor_readl(sor, SOR_LANE_SEQ_CTL);
		if ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			break;

		usleep_range(25, 100);
	}

	if ((value & SOR_LANE_SEQ_CTL_TRIGGER) != 0)
		return -ETIMEDOUT;

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->pll0);
	value |= SOR_PLL0_VCOPD | SOR_PLL0_PWR;
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_SEQ_PLLCAPPD;
	value |= SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	return 0;
}