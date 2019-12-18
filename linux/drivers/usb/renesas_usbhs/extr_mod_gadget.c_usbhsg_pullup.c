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
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_SOFT_CONNECT ; 
 int /*<<< orphan*/  usbhs_lock (struct usbhs_priv*,unsigned long) ; 
 int /*<<< orphan*/  usbhs_unlock (struct usbhs_priv*,unsigned long) ; 
 struct usbhsg_gpriv* usbhsg_gadget_to_gpriv (struct usb_gadget*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_status_clr (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_status_set (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_update_pullup (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsg_pullup(struct usb_gadget *gadget, int is_on)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	unsigned long flags;

	usbhs_lock(priv, flags);
	if (is_on)
		usbhsg_status_set(gpriv, USBHSG_STATUS_SOFT_CONNECT);
	else
		usbhsg_status_clr(gpriv, USBHSG_STATUS_SOFT_CONNECT);
	usbhsg_update_pullup(priv);
	usbhs_unlock(priv, flags);

	return 0;
}