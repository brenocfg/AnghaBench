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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_xusb_padctl {int dummy; } ;
struct tegra_xusb_lane {unsigned int index; TYPE_1__* pad; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB2_OTG_PD ; 
 int /*<<< orphan*/  USB2_OTG_PD_DR ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_OTG_PADX_CTL0 (unsigned int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_OTG_PADX_CTL1 (unsigned int) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  tegra186_utmi_bias_pad_power_off (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tegra_phy_xusb_utmi_pad_power_down(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	unsigned int index = lane->index;
	u32 value;

	if (!phy)
		return;

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value |= USB2_OTG_PD;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value |= USB2_OTG_PD_DR;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	udelay(2);

	tegra186_utmi_bias_pad_power_off(padctl);
}