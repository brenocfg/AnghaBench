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
struct peak_usb_device {TYPE_1__* adapter; int /*<<< orphan*/ * next_siblings; int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  state; struct peak_usb_device* prev_siblings; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dev_free ) (struct peak_usb_device*) ;} ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  PCAN_USB_STATE_CONNECTED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct peak_usb_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct peak_usb_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void peak_usb_disconnect(struct usb_interface *intf)
{
	struct peak_usb_device *dev;
	struct peak_usb_device *dev_prev_siblings;

	/* unregister as many netdev devices as siblings */
	for (dev = usb_get_intfdata(intf); dev; dev = dev_prev_siblings) {
		struct net_device *netdev = dev->netdev;
		char name[IFNAMSIZ];

		dev_prev_siblings = dev->prev_siblings;
		dev->state &= ~PCAN_USB_STATE_CONNECTED;
		strlcpy(name, netdev->name, IFNAMSIZ);

		unregister_netdev(netdev);

		kfree(dev->cmd_buf);
		dev->next_siblings = NULL;
		if (dev->adapter->dev_free)
			dev->adapter->dev_free(dev);

		free_candev(netdev);
		dev_info(&intf->dev, "%s removed\n", name);
	}

	usb_set_intfdata(intf, NULL);
}