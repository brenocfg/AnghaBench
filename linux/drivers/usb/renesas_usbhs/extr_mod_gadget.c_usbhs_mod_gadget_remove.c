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
struct usbhsg_gpriv {struct usbhsg_gpriv* uep; int /*<<< orphan*/  gadget; } ;
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 struct usbhsg_gpriv* usbhsg_priv_to_gpriv (struct usbhs_priv*) ; 

void usbhs_mod_gadget_remove(struct usbhs_priv *priv)
{
	struct usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	usb_del_gadget_udc(&gpriv->gadget);

	kfree(gpriv->uep);
	kfree(gpriv);
}