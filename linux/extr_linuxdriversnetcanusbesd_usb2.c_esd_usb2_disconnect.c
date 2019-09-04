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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct esd_usb2 {int net_count; TYPE_1__** nets; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_firmware ; 
 int /*<<< orphan*/  dev_attr_hardware ; 
 int /*<<< orphan*/  dev_attr_nets ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct esd_usb2*) ; 
 int /*<<< orphan*/  unlink_all_urbs (struct esd_usb2*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct esd_usb2* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esd_usb2_disconnect(struct usb_interface *intf)
{
	struct esd_usb2 *dev = usb_get_intfdata(intf);
	struct net_device *netdev;
	int i;

	device_remove_file(&intf->dev, &dev_attr_firmware);
	device_remove_file(&intf->dev, &dev_attr_hardware);
	device_remove_file(&intf->dev, &dev_attr_nets);

	usb_set_intfdata(intf, NULL);

	if (dev) {
		for (i = 0; i < dev->net_count; i++) {
			if (dev->nets[i]) {
				netdev = dev->nets[i]->netdev;
				unregister_netdev(netdev);
				free_candev(netdev);
			}
		}
		unlink_all_urbs(dev);
		kfree(dev);
	}
}