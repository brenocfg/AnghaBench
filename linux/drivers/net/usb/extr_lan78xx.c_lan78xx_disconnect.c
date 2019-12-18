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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct lan78xx_net {int /*<<< orphan*/  urb_intr; int /*<<< orphan*/  deferred; int /*<<< orphan*/  wq; struct net_device* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_KSZ9031RNX ; 
 int /*<<< orphan*/  PHY_LAN8835 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_phy_unregister (struct phy_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lan78xx_unbind (struct lan78xx_net*,struct usb_interface*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 scalar_t__ phy_is_pseudo_fixed_link (struct phy_device*) ; 
 int /*<<< orphan*/  phy_unregister_fixup_for_uid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct lan78xx_net* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan78xx_disconnect(struct usb_interface *intf)
{
	struct lan78xx_net *dev;
	struct usb_device *udev;
	struct net_device *net;
	struct phy_device *phydev;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);
	if (!dev)
		return;

	udev = interface_to_usbdev(intf);
	net = dev->net;
	phydev = net->phydev;

	phy_unregister_fixup_for_uid(PHY_KSZ9031RNX, 0xfffffff0);
	phy_unregister_fixup_for_uid(PHY_LAN8835, 0xfffffff0);

	phy_disconnect(net->phydev);

	if (phy_is_pseudo_fixed_link(phydev))
		fixed_phy_unregister(phydev);

	unregister_netdev(net);

	cancel_delayed_work_sync(&dev->wq);

	usb_scuttle_anchored_urbs(&dev->deferred);

	lan78xx_unbind(dev, intf);

	usb_kill_urb(dev->urb_intr);
	usb_free_urb(dev->urb_intr);

	free_netdev(net);
	usb_put_dev(udev);
}