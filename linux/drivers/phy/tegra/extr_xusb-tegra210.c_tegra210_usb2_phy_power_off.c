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
struct tegra_xusb_usb2_port {int /*<<< orphan*/  supply; } ;
struct tegra_xusb_usb2_pad {scalar_t__ enable; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; } ;
struct tegra_xusb_lane {int /*<<< orphan*/  index; TYPE_1__* pad; } ;
struct phy {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_BIAS_PAD_CTL0 ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_usb2_port* tegra_xusb_find_usb2_port (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_usb2_pad* to_usb2_pad (TYPE_1__*) ; 

__attribute__((used)) static int tegra210_usb2_phy_power_off(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_usb2_pad *pad = to_usb2_pad(lane->pad);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	struct tegra_xusb_usb2_port *port;
	u32 value;

	port = tegra_xusb_find_usb2_port(padctl, lane->index);
	if (!port) {
		dev_err(&phy->dev, "no port found for USB2 lane %u\n",
			lane->index);
		return -ENODEV;
	}

	mutex_lock(&padctl->lock);

	if (WARN_ON(pad->enable == 0))
		goto out;

	if (--pad->enable > 0)
		goto out;

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value |= XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

out:
	regulator_disable(port->supply);
	mutex_unlock(&padctl->lock);
	return 0;
}