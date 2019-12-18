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
typedef  int u32 ;
struct phy {int dummy; } ;
struct mvebu_a3700_utmi {scalar_t__ regs; TYPE_1__* caps; } ;
struct TYPE_2__ {int usb32; } ;

/* Variables and functions */
 int PHY_PU_OTG ; 
 int RB_USB2PHY_PU ; 
 int RB_USB2PHY_SUSPM (int) ; 
 scalar_t__ USB2_PHY_CTRL (int) ; 
 scalar_t__ USB2_PHY_OTG_CTRL ; 
 struct mvebu_a3700_utmi* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_a3700_utmi_phy_power_off(struct phy *phy)
{
	struct mvebu_a3700_utmi *utmi = phy_get_drvdata(phy);
	int usb32 = utmi->caps->usb32;
	u32 reg;

	/* Disable PHY pull-up and enable USB2 suspend */
	reg = readl(utmi->regs + USB2_PHY_CTRL(usb32));
	reg &= ~(RB_USB2PHY_PU | RB_USB2PHY_SUSPM(usb32));
	writel(reg, utmi->regs + USB2_PHY_CTRL(usb32));

	/* Power down OTG module */
	if (usb32) {
		reg = readl(utmi->regs + USB2_PHY_OTG_CTRL);
		reg &= ~PHY_PU_OTG;
		writel(reg, utmi->regs + USB2_PHY_OTG_CTRL);
	}

	return 0;
}