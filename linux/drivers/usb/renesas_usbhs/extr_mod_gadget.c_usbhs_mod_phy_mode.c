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
struct usbhs_mod_info {int /*<<< orphan*/  get_vbus; int /*<<< orphan*/ * irq_vbus; } ;
struct usbhs_priv {struct usbhs_mod_info mod_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbhsm_phy_get_vbus ; 

__attribute__((used)) static void usbhs_mod_phy_mode(struct usbhs_priv *priv)
{
	struct usbhs_mod_info *info = &priv->mod_info;

	info->irq_vbus = NULL;
	info->get_vbus = usbhsm_phy_get_vbus;

	usbhs_irq_callback_update(priv, NULL);
}