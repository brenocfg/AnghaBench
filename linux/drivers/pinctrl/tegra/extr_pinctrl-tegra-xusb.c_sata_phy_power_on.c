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
struct tegra_xusb_padctl {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1 ; 
 int XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ ; 
 int XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_S0_CTL1 ; 
 int XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET ; 
 int XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE ; 
 int XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ ; 
 int XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD ; 
 int XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_padctl* phy_get_drvdata (struct phy*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sata_phy_power_on(struct phy *phy)
{
	struct tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	unsigned long timeout;
	int err = -ETIMEDOUT;
	u32 value;

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	timeout = jiffies + msecs_to_jiffies(50);

	while (time_before(jiffies, timeout)) {
		value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
		if (value & XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET) {
			err = 0;
			break;
		}

		usleep_range(100, 200);
	}

	return err;
}