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
struct phy_meson_gxl_usb3_priv {int /*<<< orphan*/  clk_phy; int /*<<< orphan*/  clk_peripheral; int /*<<< orphan*/  regmap; int /*<<< orphan*/  mode; int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_R1 ; 
 int /*<<< orphan*/  USB_R1_U3H_FLADJ_30MHZ_REG_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct phy_meson_gxl_usb3_priv* phy_get_drvdata (struct phy*) ; 
 int phy_meson_gxl_usb3_set_mode (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb3_init(struct phy *phy)
{
	struct phy_meson_gxl_usb3_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = reset_control_reset(priv->reset);
	if (ret)
		goto err;

	ret = clk_prepare_enable(priv->clk_phy);
	if (ret)
		goto err;

	ret = clk_prepare_enable(priv->clk_peripheral);
	if (ret)
		goto err_disable_clk_phy;

	ret = phy_meson_gxl_usb3_set_mode(phy, priv->mode, 0);
	if (ret)
		goto err_disable_clk_peripheral;

	regmap_update_bits(priv->regmap, USB_R1,
			   USB_R1_U3H_FLADJ_30MHZ_REG_MASK,
			   FIELD_PREP(USB_R1_U3H_FLADJ_30MHZ_REG_MASK, 0x20));

	return 0;

err_disable_clk_peripheral:
	clk_disable_unprepare(priv->clk_peripheral);
err_disable_clk_phy:
	clk_disable_unprepare(priv->clk_phy);
err:
	return ret;
}