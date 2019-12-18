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
struct usbnet {struct asix_common_private* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct asix_common_private {int /*<<< orphan*/  (* resume ) (struct usbnet*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usbnet*) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_resume (struct usb_interface*) ; 

__attribute__((used)) static int asix_resume(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct asix_common_private *priv = dev->driver_priv;

	if (priv && priv->resume)
		priv->resume(dev);

	return usbnet_resume(intf);
}