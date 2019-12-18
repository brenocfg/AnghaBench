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
struct hi3660_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctrl; int /*<<< orphan*/  peri_crg; } ;

/* Variables and functions */
 int IP_RST_USB3OTGPHY_POR ; 
 int /*<<< orphan*/  PCTRL_PERI_CTRL3 ; 
 int PCTRL_PERI_CTRL3_MSK_START ; 
 int /*<<< orphan*/  PERI_CRG_RSTEN4 ; 
 int USB_TCXO_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct hi3660_priv* phy_get_drvdata (struct phy*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hi3660_phy_exit(struct phy *phy)
{
	struct hi3660_priv *priv = phy_get_drvdata(phy);
	u32 val;
	int ret;

	/* assert phy */
	val = IP_RST_USB3OTGPHY_POR;
	ret = regmap_write(priv->peri_crg, PERI_CRG_RSTEN4, val);
	if (ret)
		goto out;

	/* disable usb_tcxo_en */
	val = USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START;
	ret = regmap_write(priv->pctrl, PCTRL_PERI_CTRL3, val);
	if (ret)
		goto out;

	return 0;
out:
	dev_err(priv->dev, "failed to exit phy ret: %d\n", ret);
	return ret;
}