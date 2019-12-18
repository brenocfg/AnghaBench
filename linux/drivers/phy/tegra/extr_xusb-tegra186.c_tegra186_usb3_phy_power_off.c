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
struct tegra_xusb_usb3_port {int dummy; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; struct device* dev; } ;
struct tegra_xusb_lane {unsigned int index; TYPE_1__* pad; } ;
struct phy {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SSPX_ELPG_CLAMP_EN (unsigned int) ; 
 int /*<<< orphan*/  SSPX_ELPG_CLAMP_EN_EARLY (unsigned int) ; 
 int /*<<< orphan*/  SSPX_ELPG_VCORE_DOWN (unsigned int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM_1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 struct tegra_xusb_usb3_port* tegra_xusb_find_usb3_port (struct tegra_xusb_padctl*,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra186_usb3_phy_power_off(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	struct tegra_xusb_usb3_port *port;
	unsigned int index = lane->index;
	struct device *dev = padctl->dev;
	u32 value;

	port = tegra_xusb_find_usb3_port(padctl, index);
	if (!port) {
		dev_err(dev, "no port found for USB3 lane %u\n", index);
		return -ENODEV;
	}

	mutex_lock(&padctl->lock);

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(100, 200);

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_CLAMP_EN(index);
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(250, 350);

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_VCORE_DOWN(index);
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	mutex_unlock(&padctl->lock);

	return 0;
}