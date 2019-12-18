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
struct phy {int dummy; } ;
struct hi3660_priv {int eye_diagram_param; int /*<<< orphan*/  dev; int /*<<< orphan*/  otg_bc; int /*<<< orphan*/  peri_crg; int /*<<< orphan*/  pctrl; } ;

/* Variables and functions */
 int IP_RST_USB3OTG ; 
 int IP_RST_USB3OTGPHY_POR ; 
 int /*<<< orphan*/  PCTRL_PERI_CTRL3 ; 
 int PCTRL_PERI_CTRL3_MSK_START ; 
 int /*<<< orphan*/  PERI_CRG_ISODIS ; 
 int /*<<< orphan*/  PERI_CRG_RSTDIS4 ; 
 int /*<<< orphan*/  PERI_CRG_RSTEN4 ; 
 int REF_SSP_EN ; 
 int SC_USB3PHY_ABB_GT_EN ; 
 int USBOTG3CTRL2_POWERDOWN_HSP ; 
 int USBOTG3CTRL2_POWERDOWN_SSP ; 
 int /*<<< orphan*/  USBOTG3_CTRL0 ; 
 int /*<<< orphan*/  USBOTG3_CTRL2 ; 
 int /*<<< orphan*/  USBOTG3_CTRL3 ; 
 int USBOTG3_CTRL3_VBUSVLDEXT ; 
 int USBOTG3_CTRL3_VBUSVLDEXTSEL ; 
 int /*<<< orphan*/  USBOTG3_CTRL4 ; 
 int /*<<< orphan*/  USBOTG3_CTRL7 ; 
 int USB_REFCLK_ISO_EN ; 
 int USB_TCXO_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct hi3660_priv* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hi3660_phy_init(struct phy *phy)
{
	struct hi3660_priv *priv = phy_get_drvdata(phy);
	u32 val, mask;
	int ret;

	/* usb refclk iso disable */
	ret = regmap_write(priv->peri_crg, PERI_CRG_ISODIS, USB_REFCLK_ISO_EN);
	if (ret)
		goto out;

	/* enable usb_tcxo_en */
	val = USB_TCXO_EN | (USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START);
	ret = regmap_write(priv->pctrl, PCTRL_PERI_CTRL3, val);
	if (ret)
		goto out;

	/* assert phy */
	val = IP_RST_USB3OTGPHY_POR | IP_RST_USB3OTG;
	ret = regmap_write(priv->peri_crg, PERI_CRG_RSTEN4, val);
	if (ret)
		goto out;

	/* enable phy ref clk */
	val = SC_USB3PHY_ABB_GT_EN;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL0, mask, val);
	if (ret)
		goto out;

	val = REF_SSP_EN;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL7, mask, val);
	if (ret)
		goto out;

	/* exit from IDDQ mode */
	mask = USBOTG3CTRL2_POWERDOWN_HSP | USBOTG3CTRL2_POWERDOWN_SSP;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL2, mask, 0);
	if (ret)
		goto out;

	/* delay for exit from IDDQ mode */
	usleep_range(100, 120);

	/* deassert phy */
	val = IP_RST_USB3OTGPHY_POR | IP_RST_USB3OTG;
	ret = regmap_write(priv->peri_crg, PERI_CRG_RSTDIS4, val);
	if (ret)
		goto out;

	/* delay for phy deasserted */
	usleep_range(10000, 15000);

	/* fake vbus valid signal */
	val = USBOTG3_CTRL3_VBUSVLDEXT | USBOTG3_CTRL3_VBUSVLDEXTSEL;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL3, mask, val);
	if (ret)
		goto out;

	/* delay for vbus valid */
	usleep_range(100, 120);

	ret = regmap_write(priv->otg_bc, USBOTG3_CTRL4,
			priv->eye_diagram_param);
	if (ret)
		goto out;

	return 0;
out:
	dev_err(priv->dev, "failed to init phy ret: %d\n", ret);
	return ret;
}