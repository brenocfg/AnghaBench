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
struct tegra_xusb_port {struct tegra_xusb_lane* lane; } ;
struct tegra_xusb_padctl {scalar_t__ pcie; } ;
struct tegra_xusb_lane {scalar_t__ pad; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int ENODEV ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_MASK ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_VAL ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_PX_CTL1 (int /*<<< orphan*/ ) ; 
 int XUSB_PADCTL_UPHY_MISC_PAD_S0_CTL1 ; 
 int padctl_readl (struct tegra_xusb_padctl*,int) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int) ; 
 struct tegra_xusb_port* tegra_xusb_find_port (struct tegra_xusb_padctl*,char*,unsigned int) ; 

__attribute__((used)) static int tegra210_usb3_set_lfps_detect(struct tegra_xusb_padctl *padctl,
					 unsigned int index, bool enable)
{
	struct tegra_xusb_port *port;
	struct tegra_xusb_lane *lane;
	u32 value, offset;

	port = tegra_xusb_find_port(padctl, "usb3", index);
	if (!port)
		return -ENODEV;

	lane = port->lane;

	if (lane->pad == padctl->pcie)
		offset = XUSB_PADCTL_UPHY_MISC_PAD_PX_CTL1(lane->index);
	else
		offset = XUSB_PADCTL_UPHY_MISC_PAD_S0_CTL1;

	value = padctl_readl(padctl, offset);

	value &= ~((XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_MASK <<
		    XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT) |
		   XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN |
		   XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD);

	if (!enable) {
		value |= (XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_VAL <<
			  XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT) |
			 XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN |
			 XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD;
	}

	padctl_writel(padctl, value, offset);

	return 0;
}