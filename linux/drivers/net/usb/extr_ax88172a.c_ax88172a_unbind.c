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
struct usbnet {struct ax88172a_private* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct ax88172a_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax88172a_remove_mdio (struct usbnet*) ; 
 int /*<<< orphan*/  kfree (struct ax88172a_private*) ; 

__attribute__((used)) static void ax88172a_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct ax88172a_private *priv = dev->driver_priv;

	ax88172a_remove_mdio(dev);
	kfree(priv);
}