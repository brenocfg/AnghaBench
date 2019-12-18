#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  kobj; } ;
struct usb_port {TYPE_7__ dev; } ;
struct usb_hub {int /*<<< orphan*/  child_usage_bits; struct usb_port** ports; } ;
struct TYPE_17__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  devt; } ;
struct usb_device {int devnum; int portnum; TYPE_2__ dev; int /*<<< orphan*/  ep0; scalar_t__ parent; scalar_t__ manufacturer; scalar_t__ product; scalar_t__ serial; TYPE_1__* bus; } ;
struct TYPE_16__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_DEVICE_MAJOR ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  add_device_randomness (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  announce_device (struct usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_7__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  set_usb_port_removable (struct usb_device*) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_create_ep_devs (TYPE_2__*,int /*<<< orphan*/ *,struct usb_device*) ; 
 int /*<<< orphan*/  usb_disable_autosuspend (struct usb_device*) ; 
 int usb_enumerate_device (struct usb_device*) ; 
 struct usb_hub* usb_hub_to_struct_hub (scalar_t__) ; 
 int /*<<< orphan*/  usb_mark_last_busy (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 

int usb_new_device(struct usb_device *udev)
{
	int err;

	if (udev->parent) {
		/* Initialize non-root-hub device wakeup to disabled;
		 * device (un)configuration controls wakeup capable
		 * sysfs power/wakeup controls wakeup enabled/disabled
		 */
		device_init_wakeup(&udev->dev, 0);
	}

	/* Tell the runtime-PM framework the device is active */
	pm_runtime_set_active(&udev->dev);
	pm_runtime_get_noresume(&udev->dev);
	pm_runtime_use_autosuspend(&udev->dev);
	pm_runtime_enable(&udev->dev);

	/* By default, forbid autosuspend for all devices.  It will be
	 * allowed for hubs during binding.
	 */
	usb_disable_autosuspend(udev);

	err = usb_enumerate_device(udev);	/* Read descriptors */
	if (err < 0)
		goto fail;
	dev_dbg(&udev->dev, "udev %d, busnum %d, minor = %d\n",
			udev->devnum, udev->bus->busnum,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));
	/* export the usbdev device-node for libusb */
	udev->dev.devt = MKDEV(USB_DEVICE_MAJOR,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));

	/* Tell the world! */
	announce_device(udev);

	if (udev->serial)
		add_device_randomness(udev->serial, strlen(udev->serial));
	if (udev->product)
		add_device_randomness(udev->product, strlen(udev->product));
	if (udev->manufacturer)
		add_device_randomness(udev->manufacturer,
				      strlen(udev->manufacturer));

	device_enable_async_suspend(&udev->dev);

	/* check whether the hub or firmware marks this port as non-removable */
	if (udev->parent)
		set_usb_port_removable(udev);

	/* Register the device.  The device driver is responsible
	 * for configuring the device and invoking the add-device
	 * notifier chain (used by usbfs and possibly others).
	 */
	err = device_add(&udev->dev);
	if (err) {
		dev_err(&udev->dev, "can't device_add, error %d\n", err);
		goto fail;
	}

	/* Create link files between child device and usb port device. */
	if (udev->parent) {
		struct usb_hub *hub = usb_hub_to_struct_hub(udev->parent);
		int port1 = udev->portnum;
		struct usb_port	*port_dev = hub->ports[port1 - 1];

		err = sysfs_create_link(&udev->dev.kobj,
				&port_dev->dev.kobj, "port");
		if (err)
			goto fail;

		err = sysfs_create_link(&port_dev->dev.kobj,
				&udev->dev.kobj, "device");
		if (err) {
			sysfs_remove_link(&udev->dev.kobj, "port");
			goto fail;
		}

		if (!test_and_set_bit(port1, hub->child_usage_bits))
			pm_runtime_get_sync(&port_dev->dev);
	}

	(void) usb_create_ep_devs(&udev->dev, &udev->ep0, udev);
	usb_mark_last_busy(udev);
	pm_runtime_put_sync_autosuspend(&udev->dev);
	return err;

fail:
	usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	pm_runtime_disable(&udev->dev);
	pm_runtime_set_suspended(&udev->dev);
	return err;
}