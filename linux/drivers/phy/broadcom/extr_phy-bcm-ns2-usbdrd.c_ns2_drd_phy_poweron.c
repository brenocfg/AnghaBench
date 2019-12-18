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
typedef  scalar_t__ u32 ;
struct phy {int /*<<< orphan*/  dev; } ;
struct ns2_phy_driver {scalar_t__ usb2h_strap_reg; scalar_t__ idmdrd_rst_ctrl; scalar_t__ crmu_usb2_ctrl; scalar_t__ icfgdrd_regs; } ;
struct ns2_phy_data {scalar_t__ new_state; struct ns2_phy_driver* driver; } ;

/* Variables and functions */
 scalar_t__ AFE_CORERDY_VDDC ; 
 scalar_t__ DRD_DEV_MODE ; 
 scalar_t__ DRD_DEV_VAL ; 
 scalar_t__ DRD_HOST_VAL ; 
 scalar_t__ EVT_DEVICE ; 
 scalar_t__ ICFG_DRD_P0CTL ; 
 int /*<<< orphan*/  ICFG_MISC_STAT ; 
 scalar_t__ IDM_RST_BIT ; 
 scalar_t__ OHCI_OVRCUR_POL ; 
 int /*<<< orphan*/  PHY_PLL_LOCK ; 
 scalar_t__ PHY_PLL_RESETB ; 
 scalar_t__ PHY_RESETB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ns2_phy_data* phy_get_drvdata (struct phy*) ; 
 int pll_lock_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ns2_phy_driver*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ns2_drd_phy_poweron(struct phy *phy)
{
	struct ns2_phy_data *data = phy_get_drvdata(phy);
	struct ns2_phy_driver *driver = data->driver;
	u32 extcon_event = data->new_state;
	int ret;
	u32 val;

	if (extcon_event == EVT_DEVICE) {
		writel(DRD_DEV_VAL, driver->icfgdrd_regs + ICFG_DRD_P0CTL);

		val = readl(driver->idmdrd_rst_ctrl);
		val &= ~IDM_RST_BIT;
		writel(val, driver->idmdrd_rst_ctrl);

		val = readl(driver->crmu_usb2_ctrl);
		val |= (AFE_CORERDY_VDDC | DRD_DEV_MODE);
		writel(val, driver->crmu_usb2_ctrl);

		/* Bring PHY and PHY_PLL out of Reset */
		val = readl(driver->crmu_usb2_ctrl);
		val |= (PHY_PLL_RESETB | PHY_RESETB);
		writel(val, driver->crmu_usb2_ctrl);

		ret = pll_lock_stat(ICFG_MISC_STAT, PHY_PLL_LOCK, driver);
		if (ret < 0) {
			dev_err(&phy->dev, "Phy PLL lock failed\n");
			return ret;
		}
	} else {
		writel(DRD_HOST_VAL, driver->icfgdrd_regs + ICFG_DRD_P0CTL);

		val = readl(driver->crmu_usb2_ctrl);
		val |= AFE_CORERDY_VDDC;
		writel(val, driver->crmu_usb2_ctrl);

		ret = pll_lock_stat(ICFG_MISC_STAT, PHY_PLL_LOCK, driver);
		if (ret < 0) {
			dev_err(&phy->dev, "Phy PLL lock failed\n");
			return ret;
		}

		val = readl(driver->idmdrd_rst_ctrl);
		val &= ~IDM_RST_BIT;
		writel(val, driver->idmdrd_rst_ctrl);

		/* port over current Polarity */
		val = readl(driver->usb2h_strap_reg);
		val |= OHCI_OVRCUR_POL;
		writel(val, driver->usb2h_strap_reg);
	}

	return 0;
}