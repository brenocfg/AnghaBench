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
struct dwc3_meson_g12a {int /*<<< orphan*/  regmap; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int PHY_MODE_USB_HOST ; 
 scalar_t__ U2P_R0 ; 
 int /*<<< orphan*/  U2P_R0_HOST_DEVICE ; 
 int U2P_REG_SIZE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_meson_g12a_usb2_set_mode(struct dwc3_meson_g12a *priv,
					  int i, enum phy_mode mode)
{
	if (mode == PHY_MODE_USB_HOST)
		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				U2P_R0_HOST_DEVICE,
				U2P_R0_HOST_DEVICE);
	else
		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				U2P_R0_HOST_DEVICE, 0);
}