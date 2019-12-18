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
struct phy_meson_gxl_usb2_priv {int mode; int /*<<< orphan*/  regmap; } ;
struct phy {int dummy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 int /*<<< orphan*/  U2P_R0 ; 
 int /*<<< orphan*/  U2P_R0_DM_PULLDOWN ; 
 int /*<<< orphan*/  U2P_R0_DP_PULLDOWN ; 
 int /*<<< orphan*/  U2P_R0_ID_PULLUP ; 
 struct phy_meson_gxl_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_meson_gxl_usb2_reset (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb2_set_mode(struct phy *phy,
				       enum phy_mode mode, int submode)
{
	struct phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	switch (mode) {
	case PHY_MODE_USB_HOST:
	case PHY_MODE_USB_OTG:
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DM_PULLDOWN,
				   U2P_R0_DM_PULLDOWN);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DP_PULLDOWN,
				   U2P_R0_DP_PULLDOWN);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_ID_PULLUP, 0);
		break;

	case PHY_MODE_USB_DEVICE:
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DM_PULLDOWN,
				   0);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DP_PULLDOWN,
				   0);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_ID_PULLUP,
				   U2P_R0_ID_PULLUP);
		break;

	default:
		return -EINVAL;
	}

	phy_meson_gxl_usb2_reset(phy);

	priv->mode = mode;

	return 0;
}