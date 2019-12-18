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
struct usbhsg_gpriv {int vbus_active; } ;
struct usbhs_priv {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct platform_device* usbhs_priv_to_pdev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsc_schedule_notify_hotplug (struct platform_device*) ; 
 struct usbhsg_gpriv* usbhsg_gadget_to_gpriv (struct usb_gadget*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 

__attribute__((used)) static int usbhsg_vbus_session(struct usb_gadget *gadget, int is_active)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	struct platform_device *pdev = usbhs_priv_to_pdev(priv);

	gpriv->vbus_active = !!is_active;

	usbhsc_schedule_notify_hotplug(pdev);

	return 0;
}