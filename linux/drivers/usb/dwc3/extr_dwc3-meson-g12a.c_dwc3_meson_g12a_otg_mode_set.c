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
struct dwc3_meson_g12a {int otg_phy_mode; scalar_t__ vbus; int /*<<< orphan*/  dev; int /*<<< orphan*/ * phys; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
 int PHY_MODE_USB_DEVICE ; 
 int PHY_MODE_USB_HOST ; 
 size_t USB2_OTG_PHY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_meson_g12a_usb2_set_mode (struct dwc3_meson_g12a*,size_t,int) ; 
 int /*<<< orphan*/  dwc3_meson_g12a_usb_otg_apply_mode (struct dwc3_meson_g12a*) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int dwc3_meson_g12a_otg_mode_set(struct dwc3_meson_g12a *priv,
					enum phy_mode mode)
{
	int ret;

	if (!priv->phys[USB2_OTG_PHY])
		return -EINVAL;

	if (mode == PHY_MODE_USB_HOST)
		dev_info(priv->dev, "switching to Host Mode\n");
	else
		dev_info(priv->dev, "switching to Device Mode\n");

	if (priv->vbus) {
		if (mode == PHY_MODE_USB_DEVICE)
			ret = regulator_disable(priv->vbus);
		else
			ret = regulator_enable(priv->vbus);
		if (ret)
			return ret;
	}

	priv->otg_phy_mode = mode;

	dwc3_meson_g12a_usb2_set_mode(priv, USB2_OTG_PHY, mode);

	dwc3_meson_g12a_usb_otg_apply_mode(priv);

	return 0;
}