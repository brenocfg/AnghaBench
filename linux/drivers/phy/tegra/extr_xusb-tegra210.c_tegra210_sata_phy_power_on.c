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
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; } ;
struct tegra_xusb_lane {int /*<<< orphan*/  index; TYPE_1__* pad; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_PADCTL_USB3_PAD_MUX ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 int tegra210_sata_uphy_enable (struct tegra_xusb_padctl*,int) ; 

__attribute__((used)) static int tegra210_sata_phy_power_on(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;
	int err;

	mutex_lock(&padctl->lock);

	err = tegra210_sata_uphy_enable(padctl, false);
	if (err < 0)
		goto unlock;

	value = padctl_readl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(lane->index);
	padctl_writel(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

unlock:
	mutex_unlock(&padctl->lock);
	return err;
}