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
struct phy_meson_gxl_usb3_priv {int mode; int /*<<< orphan*/  regmap; } ;
struct phy {int /*<<< orphan*/  dev; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_MODE_USB_DEVICE 129 
#define  PHY_MODE_USB_HOST 128 
 int /*<<< orphan*/  USB_R0 ; 
 int /*<<< orphan*/  USB_R0_U2D_ACT ; 
 int /*<<< orphan*/  USB_R4 ; 
 int /*<<< orphan*/  USB_R4_P21_SLEEP_M0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct phy_meson_gxl_usb3_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb3_set_mode(struct phy *phy,
				       enum phy_mode mode, int submode)
{
	struct phy_meson_gxl_usb3_priv *priv = phy_get_drvdata(phy);

	switch (mode) {
	case PHY_MODE_USB_HOST:
		regmap_update_bits(priv->regmap, USB_R0, USB_R0_U2D_ACT, 0);
		regmap_update_bits(priv->regmap, USB_R4, USB_R4_P21_SLEEP_M0,
				   0);
		break;

	case PHY_MODE_USB_DEVICE:
		regmap_update_bits(priv->regmap, USB_R0, USB_R0_U2D_ACT,
				   USB_R0_U2D_ACT);
		regmap_update_bits(priv->regmap, USB_R4, USB_R4_P21_SLEEP_M0,
				   USB_R4_P21_SLEEP_M0);
		break;

	default:
		dev_err(&phy->dev, "unsupported PHY mode %d\n", mode);
		return -EINVAL;
	}

	priv->mode = mode;

	return 0;
}