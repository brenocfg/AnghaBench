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
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM ; 
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN ; 
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY ; 
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_xusb_padctl_enable(struct tegra_xusb_padctl *padctl)
{
	u32 value;

	mutex_lock(&padctl->lock);

	if (padctl->enable++ > 0)
		goto out;

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_readl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	padctl_writel(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

out:
	mutex_unlock(&padctl->lock);
	return 0;
}