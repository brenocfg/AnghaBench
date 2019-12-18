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
struct phy_meson_gxl_usb2_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct phy_meson_gxl_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb2_init(struct phy *phy)
{
	struct phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = reset_control_reset(priv->reset);
	if (ret)
		return ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	return 0;
}