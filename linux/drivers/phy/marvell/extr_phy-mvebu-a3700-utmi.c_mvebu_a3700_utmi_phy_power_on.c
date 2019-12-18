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
struct device {int dummy; } ;
struct phy {struct device dev; } ;
struct mvebu_a3700_utmi {scalar_t__ regs; int /*<<< orphan*/  usb_misc; TYPE_1__* caps; } ;
struct TYPE_2__ {int usb32; } ;

/* Variables and functions */
 int PHY_CDP_DM_AUTO ; 
 int PHY_CDP_EN ; 
 int PHY_DCP_EN ; 
 int PHY_ENSWITCH_DM ; 
 int PHY_ENSWITCH_DP ; 
 int PHY_IMPCAL_DONE ; 
 int PHY_PD_EN ; 
 int PHY_PLLCAL_DONE ; 
 int PHY_PU_CHRG_DTC ; 
 int PHY_PU_OTG ; 
 int PLL_FB_DIV_96 ; 
 int PLL_FB_DIV_MASK ; 
 int PLL_FB_DIV_OFF ; 
 int /*<<< orphan*/  PLL_LOCK_DELAY_US ; 
 int /*<<< orphan*/  PLL_LOCK_TIMEOUT_US ; 
 int PLL_READY ; 
 int PLL_REF_DIV_5 ; 
 int PLL_REF_DIV_MASK ; 
 int PLL_REF_DIV_OFF ; 
 int PLL_SEL_LPFR_MASK ; 
 int RB_USB2PHY_PU ; 
 int RB_USB2PHY_SUSPM (int) ; 
 int USB2PHY_SQCAL_DONE ; 
 int USB2_DM_PULLDN_DEV_MODE ; 
 int USB2_DP_PULLDN_DEV_MODE ; 
 scalar_t__ USB2_PHY_CAL_CTRL ; 
 scalar_t__ USB2_PHY_CHRGR_DETECT ; 
 int /*<<< orphan*/  USB2_PHY_CTRL (int) ; 
 scalar_t__ USB2_PHY_OTG_CTRL ; 
 scalar_t__ USB2_PHY_PLL_CTRL_REG0 ; 
 scalar_t__ USB2_RX_CHAN_CTRL1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct mvebu_a3700_utmi* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_a3700_utmi_phy_power_on(struct phy *phy)
{
	struct mvebu_a3700_utmi *utmi = phy_get_drvdata(phy);
	struct device *dev = &phy->dev;
	int usb32 = utmi->caps->usb32;
	int ret = 0;
	u32 reg;

	/*
	 * Setup PLL. 40MHz clock used to be the default, being 25MHz now.
	 * See "PLL Settings for Typical REFCLK" table.
	 */
	reg = readl(utmi->regs + USB2_PHY_PLL_CTRL_REG0);
	reg &= ~(PLL_REF_DIV_MASK | PLL_FB_DIV_MASK | PLL_SEL_LPFR_MASK);
	reg |= (PLL_REF_DIV_5 << PLL_REF_DIV_OFF) |
	       (PLL_FB_DIV_96 << PLL_FB_DIV_OFF);
	writel(reg, utmi->regs + USB2_PHY_PLL_CTRL_REG0);

	/* Enable PHY pull up and disable USB2 suspend */
	regmap_update_bits(utmi->usb_misc, USB2_PHY_CTRL(usb32),
			   RB_USB2PHY_SUSPM(usb32) | RB_USB2PHY_PU,
			   RB_USB2PHY_SUSPM(usb32) | RB_USB2PHY_PU);

	if (usb32) {
		/* Power up OTG module */
		reg = readl(utmi->regs + USB2_PHY_OTG_CTRL);
		reg |= PHY_PU_OTG;
		writel(reg, utmi->regs + USB2_PHY_OTG_CTRL);

		/* Disable PHY charger detection */
		reg = readl(utmi->regs + USB2_PHY_CHRGR_DETECT);
		reg &= ~(PHY_CDP_EN | PHY_DCP_EN | PHY_PD_EN | PHY_PU_CHRG_DTC |
			 PHY_CDP_DM_AUTO | PHY_ENSWITCH_DP | PHY_ENSWITCH_DM);
		writel(reg, utmi->regs + USB2_PHY_CHRGR_DETECT);

		/* Disable PHY DP/DM pull-down (used for device mode) */
		regmap_update_bits(utmi->usb_misc, USB2_PHY_CTRL(usb32),
				   USB2_DP_PULLDN_DEV_MODE |
				   USB2_DM_PULLDN_DEV_MODE, 0);
	}

	/* Wait for PLL calibration */
	ret = readl_poll_timeout(utmi->regs + USB2_PHY_CAL_CTRL, reg,
				 reg & PHY_PLLCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	if (ret) {
		dev_err(dev, "Failed to end USB2 PLL calibration\n");
		return ret;
	}

	/* Wait for impedance calibration */
	ret = readl_poll_timeout(utmi->regs + USB2_PHY_CAL_CTRL, reg,
				 reg & PHY_IMPCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	if (ret) {
		dev_err(dev, "Failed to end USB2 impedance calibration\n");
		return ret;
	}

	/* Wait for squelch calibration */
	ret = readl_poll_timeout(utmi->regs + USB2_RX_CHAN_CTRL1, reg,
				 reg & USB2PHY_SQCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	if (ret) {
		dev_err(dev, "Failed to end USB2 unknown calibration\n");
		return ret;
	}

	/* Wait for PLL to be locked */
	ret = readl_poll_timeout(utmi->regs + USB2_PHY_PLL_CTRL_REG0, reg,
				 reg & PLL_READY,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	if (ret)
		dev_err(dev, "Failed to lock USB2 PLL\n");

	return ret;
}