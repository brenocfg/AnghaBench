#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct usb_port {TYPE_2__ dev; } ;
struct usb_hub {int /*<<< orphan*/  child_usage_bits; struct usb_port** ports; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct usb_device {int portnum; TYPE_1__ dev; int /*<<< orphan*/  ep0; scalar_t__ parent; int /*<<< orphan*/  devnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_state_lock ; 
 int /*<<< orphan*/  hub_disconnect_children (struct usb_device*) ; 
 int /*<<< orphan*/  hub_free_dev (struct usb_device*) ; 
 int /*<<< orphan*/  pm_runtime_barrier (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  release_devnum (struct usb_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_disable_device (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_synchronize_unlinks (struct usb_device*) ; 
 struct usb_hub* usb_hub_to_struct_hub (scalar_t__) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_remove_ep_devs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

void usb_disconnect(struct usb_device **pdev)
{
	struct usb_port *port_dev = NULL;
	struct usb_device *udev = *pdev;
	struct usb_hub *hub = NULL;
	int port1 = 1;

	/* mark the device as inactive, so any further urb submissions for
	 * this device (and any of its children) will fail immediately.
	 * this quiesces everything except pending urbs.
	 */
	usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	dev_info(&udev->dev, "USB disconnect, device number %d\n",
			udev->devnum);

	/*
	 * Ensure that the pm runtime code knows that the USB device
	 * is in the process of being disconnected.
	 */
	pm_runtime_barrier(&udev->dev);

	usb_lock_device(udev);

	hub_disconnect_children(udev);

	/* deallocate hcd/hardware state ... nuking all pending urbs and
	 * cleaning up all state associated with the current configuration
	 * so that the hardware is now fully quiesced.
	 */
	dev_dbg(&udev->dev, "unregistering device\n");
	usb_disable_device(udev, 0);
	usb_hcd_synchronize_unlinks(udev);

	if (udev->parent) {
		port1 = udev->portnum;
		hub = usb_hub_to_struct_hub(udev->parent);
		port_dev = hub->ports[port1 - 1];

		sysfs_remove_link(&udev->dev.kobj, "port");
		sysfs_remove_link(&port_dev->dev.kobj, "device");

		/*
		 * As usb_port_runtime_resume() de-references udev, make
		 * sure no resumes occur during removal
		 */
		if (!test_and_set_bit(port1, hub->child_usage_bits))
			pm_runtime_get_sync(&port_dev->dev);
	}

	usb_remove_ep_devs(&udev->ep0);
	usb_unlock_device(udev);

	/* Unregister the device.  The device driver is responsible
	 * for de-configuring the device and invoking the remove-device
	 * notifier chain (used by usbfs and possibly others).
	 */
	device_del(&udev->dev);

	/* Free the device number and delete the parent's children[]
	 * (or root_hub) pointer.
	 */
	release_devnum(udev);

	/* Avoid races with recursively_mark_NOTATTACHED() */
	spin_lock_irq(&device_state_lock);
	*pdev = NULL;
	spin_unlock_irq(&device_state_lock);

	if (port_dev && test_and_clear_bit(port1, hub->child_usage_bits))
		pm_runtime_put(&port_dev->dev);

	hub_free_dev(udev);

	put_device(&udev->dev);
}