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
struct dwc3_meson_g12a {int /*<<< orphan*/  regmap; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int PHY_MODE_USB_DEVICE ; 
 int PHY_MODE_USB_HOST ; 
 int /*<<< orphan*/  USB_R5 ; 
 int USB_R5_ID_DIG_REG ; 
 int USB_R5_ID_DIG_SYNC ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static enum phy_mode dwc3_meson_g12a_get_id(struct dwc3_meson_g12a *priv)
{
	u32 reg;

	regmap_read(priv->regmap, USB_R5, &reg);

	if (reg & (USB_R5_ID_DIG_SYNC | USB_R5_ID_DIG_REG))
		return PHY_MODE_USB_DEVICE;

	return PHY_MODE_USB_HOST;
}