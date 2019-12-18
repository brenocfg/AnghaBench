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

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  USB_R1 ; 
 int USB_R1_P30_PCS_TX_SWING_FULL_MASK ; 
 int USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT ; 
 int /*<<< orphan*/  USB_R2 ; 
 int USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK ; 
 int USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK ; 
 int /*<<< orphan*/  USB_R3 ; 
 int USB_R3_P30_REF_SSP_EN ; 
 int USB_R3_P30_SSC_ENABLE ; 
 int USB_R3_P30_SSC_RANGE_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc3_meson_g12a_usb3_init(struct dwc3_meson_g12a *priv)
{
	regmap_update_bits(priv->regmap, USB_R3,
			USB_R3_P30_SSC_RANGE_MASK |
			USB_R3_P30_REF_SSP_EN,
			USB_R3_P30_SSC_ENABLE |
			FIELD_PREP(USB_R3_P30_SSC_RANGE_MASK, 2) |
			USB_R3_P30_REF_SSP_EN);
	udelay(2);

	regmap_update_bits(priv->regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK, 0x15));

	regmap_update_bits(priv->regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK, 0x20));

	udelay(2);

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT);

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_P30_PCS_TX_SWING_FULL_MASK,
			FIELD_PREP(USB_R1_P30_PCS_TX_SWING_FULL_MASK, 127));
}