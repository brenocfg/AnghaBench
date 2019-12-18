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
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 struct usb_hcd* usbhsh_hpriv_to_hcd (struct usbhsh_hpriv*) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

int usbhs_mod_host_remove(struct usbhs_priv *priv)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);

	usb_put_hcd(hcd);

	return 0;
}