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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_xusb_padctl {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1 ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1 ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_padctl* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int sata_phy_power_off(struct phy *phy)
{
	struct tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	u32 value;

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	return 0;
}