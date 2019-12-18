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
struct dwc3_meson_g12a {int otg_phy_mode; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USB_R5 ; 
 int /*<<< orphan*/  USB_R5_ID_DIG_IRQ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dwc3_meson_g12a_get_id (struct dwc3_meson_g12a*) ; 
 scalar_t__ dwc3_meson_g12a_otg_mode_set (struct dwc3_meson_g12a*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dwc3_meson_g12a_irq_thread(int irq, void *data)
{
	struct dwc3_meson_g12a *priv = data;
	enum phy_mode otg_id;

	otg_id = dwc3_meson_g12a_get_id(priv);
	if (otg_id != priv->otg_phy_mode) {
		if (dwc3_meson_g12a_otg_mode_set(priv, otg_id))
			dev_warn(priv->dev, "Failed to switch OTG mode\n");
	}

	regmap_update_bits(priv->regmap, USB_R5, USB_R5_ID_DIG_IRQ, 0);

	return IRQ_HANDLED;
}