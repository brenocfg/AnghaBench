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
struct dwc3_meson_g12a {scalar_t__ usb3_ports; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_R1 ; 
 int /*<<< orphan*/  USB_R1_U3H_FLADJ_30MHZ_REG_MASK ; 
 int /*<<< orphan*/  USB_R5 ; 
 int /*<<< orphan*/  USB_R5_ID_DIG_EN_0 ; 
 int /*<<< orphan*/  USB_R5_ID_DIG_EN_1 ; 
 int /*<<< orphan*/  USB_R5_ID_DIG_TH_MASK ; 
 int dwc3_meson_g12a_usb2_init (struct dwc3_meson_g12a*) ; 
 int /*<<< orphan*/  dwc3_meson_g12a_usb3_init (struct dwc3_meson_g12a*) ; 
 int /*<<< orphan*/  dwc3_meson_g12a_usb_otg_apply_mode (struct dwc3_meson_g12a*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_meson_g12a_usb_init(struct dwc3_meson_g12a *priv)
{
	int ret;

	ret = dwc3_meson_g12a_usb2_init(priv);
	if (ret)
		return ret;

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_U3H_FLADJ_30MHZ_REG_MASK,
			FIELD_PREP(USB_R1_U3H_FLADJ_30MHZ_REG_MASK, 0x20));

	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_EN_0,
			USB_R5_ID_DIG_EN_0);
	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_EN_1,
			USB_R5_ID_DIG_EN_1);
	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_TH_MASK,
			FIELD_PREP(USB_R5_ID_DIG_TH_MASK, 0xff));

	/* If we have an actual SuperSpeed port, initialize it */
	if (priv->usb3_ports)
		dwc3_meson_g12a_usb3_init(priv);

	dwc3_meson_g12a_usb_otg_apply_mode(priv);

	return 0;
}