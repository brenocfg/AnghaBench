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
struct phy_meson_gxl_usb2_priv {int is_enabled; int /*<<< orphan*/  mode; int /*<<< orphan*/  regmap; } ;
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  U2P_R0 ; 
 int /*<<< orphan*/  U2P_R0_POWER_ON_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct phy_meson_gxl_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_meson_gxl_usb2_power_off (struct phy*) ; 
 int phy_meson_gxl_usb2_set_mode (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb2_power_on(struct phy *phy)
{
	struct phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);
	int ret;

	priv->is_enabled = 1;

	/* power on the PHY by taking it out of reset mode */
	regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET, 0);

	ret = phy_meson_gxl_usb2_set_mode(phy, priv->mode, 0);
	if (ret) {
		phy_meson_gxl_usb2_power_off(phy);

		dev_err(&phy->dev, "Failed to initialize PHY with mode %d\n",
			priv->mode);
		return ret;
	}

	return 0;
}