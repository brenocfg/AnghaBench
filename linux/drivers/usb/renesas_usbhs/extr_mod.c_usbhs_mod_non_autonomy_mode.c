#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbhs_priv {TYPE_1__* pfunc; } ;
struct usbhs_mod_info {int /*<<< orphan*/  get_vbus; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_vbus; } ;

/* Variables and functions */
 struct usbhs_mod_info* usbhs_priv_to_modinfo (struct usbhs_priv*) ; 

void usbhs_mod_non_autonomy_mode(struct usbhs_priv *priv)
{
	struct usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	info->get_vbus = priv->pfunc->get_vbus;
}