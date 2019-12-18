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
 int usbhs_frame_get_num (struct usbhs_priv*) ; 
 struct usbhsg_gpriv* usbhsg_gadget_to_gpriv (struct usb_gadget*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 

__attribute__((used)) static int usbhsg_get_frame(struct usb_gadget *gadget)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	return usbhs_frame_get_num(priv);
}