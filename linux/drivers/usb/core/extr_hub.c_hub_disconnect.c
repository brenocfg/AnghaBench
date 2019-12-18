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
struct usb_hub {int disconnected; int /*<<< orphan*/  kref; int /*<<< orphan*/  buffer; int /*<<< orphan*/  status; int /*<<< orphan*/  descriptor; int /*<<< orphan*/  ports; int /*<<< orphan*/  urb; TYPE_1__* hdev; scalar_t__ error; } ;
struct usb_device {int maxchild; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_DISCONNECT ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  device_state_lock ; 
 int /*<<< orphan*/  highspeed_hubs ; 
 int /*<<< orphan*/  hub_quiesce (struct usb_hub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_release ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_hub_remove_port_device (struct usb_hub*,int) ; 
 int /*<<< orphan*/  usb_port_peer_mutex ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hub_disconnect(struct usb_interface *intf)
{
	struct usb_hub *hub = usb_get_intfdata(intf);
	struct usb_device *hdev = interface_to_usbdev(intf);
	int port1;

	/*
	 * Stop adding new hub events. We do not want to block here and thus
	 * will not try to remove any pending work item.
	 */
	hub->disconnected = 1;

	/* Disconnect all children and quiesce the hub */
	hub->error = 0;
	hub_quiesce(hub, HUB_DISCONNECT);

	mutex_lock(&usb_port_peer_mutex);

	/* Avoid races with recursively_mark_NOTATTACHED() */
	spin_lock_irq(&device_state_lock);
	port1 = hdev->maxchild;
	hdev->maxchild = 0;
	usb_set_intfdata(intf, NULL);
	spin_unlock_irq(&device_state_lock);

	for (; port1 > 0; --port1)
		usb_hub_remove_port_device(hub, port1);

	mutex_unlock(&usb_port_peer_mutex);

	if (hub->hdev->speed == USB_SPEED_HIGH)
		highspeed_hubs--;

	usb_free_urb(hub->urb);
	kfree(hub->ports);
	kfree(hub->descriptor);
	kfree(hub->status);
	kfree(hub->buffer);

	pm_suspend_ignore_children(&intf->dev, false);
	kref_put(&hub->kref, hub_release);
}