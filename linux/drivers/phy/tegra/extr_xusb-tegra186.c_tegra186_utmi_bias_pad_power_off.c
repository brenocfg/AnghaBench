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
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; } ;
struct tegra186_xusb_padctl {scalar_t__ bias_pad_enable; int /*<<< orphan*/  usb2_trk_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB2_PD_TRK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_BIAS_PAD_CTL1 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra186_xusb_padctl* to_tegra186_xusb_padctl (struct tegra_xusb_padctl*) ; 

__attribute__((used)) static void tegra186_utmi_bias_pad_power_off(struct tegra_xusb_padctl *padctl)
{
	struct tegra186_xusb_padctl *priv = to_tegra186_xusb_padctl(padctl);
	u32 value;

	mutex_lock(&padctl->lock);

	if (WARN_ON(priv->bias_pad_enable == 0)) {
		mutex_unlock(&padctl->lock);
		return;
	}

	if (--priv->bias_pad_enable > 0) {
		mutex_unlock(&padctl->lock);
		return;
	}

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value |= USB2_PD_TRK;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	clk_disable_unprepare(priv->usb2_trk_clk);

	mutex_unlock(&padctl->lock);
}