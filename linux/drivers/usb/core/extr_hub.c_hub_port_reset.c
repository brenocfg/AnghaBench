#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct usb_port {int quirks; int /*<<< orphan*/  dev; } ;
struct usb_hub {TYPE_2__* hdev; int /*<<< orphan*/ * intfdev; int /*<<< orphan*/  warm_reset_bits; struct usb_port** ports; } ;
struct usb_hcd {TYPE_1__* driver; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {int quirks; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_device ) (struct usb_hcd*,struct usb_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOTCONN ; 
 unsigned int HUB_LONG_RESET_TIME ; 
 int PORT_RESET_TRIES ; 
 int /*<<< orphan*/  USB_PORT_FEAT_BH_PORT_RESET ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_BH_PORT_RESET ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_CONNECTION ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_PORT_LINK_STATE ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_RESET ; 
 int /*<<< orphan*/  USB_PORT_FEAT_RESET ; 
 int USB_PORT_QUIRK_FAST_ENUM ; 
 int USB_QUIRK_HUB_SLOW_RESET ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_cf_port_reset_rwsem ; 
 int /*<<< orphan*/  hub_is_superspeed (TYPE_2__*) ; 
 scalar_t__ hub_port_status (struct usb_hub*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hub_port_wait_reset (struct usb_hub*,int,struct usb_device*,unsigned int,int) ; 
 scalar_t__ hub_port_warm_reset_required (struct usb_hub*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int set_port_feature (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_devnum (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clear_port_feature (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hub_port_reset(struct usb_hub *hub, int port1,
			struct usb_device *udev, unsigned int delay, bool warm)
{
	int i, status;
	u16 portchange, portstatus;
	struct usb_port *port_dev = hub->ports[port1 - 1];
	int reset_recovery_time;

	if (!hub_is_superspeed(hub->hdev)) {
		if (warm) {
			dev_err(hub->intfdev, "only USB3 hub support "
						"warm reset\n");
			return -EINVAL;
		}
		/* Block EHCI CF initialization during the port reset.
		 * Some companion controllers don't like it when they mix.
		 */
		down_read(&ehci_cf_port_reset_rwsem);
	} else if (!warm) {
		/*
		 * If the caller hasn't explicitly requested a warm reset,
		 * double check and see if one is needed.
		 */
		if (hub_port_status(hub, port1, &portstatus, &portchange) == 0)
			if (hub_port_warm_reset_required(hub, port1,
							portstatus))
				warm = true;
	}
	clear_bit(port1, hub->warm_reset_bits);

	/* Reset the port */
	for (i = 0; i < PORT_RESET_TRIES; i++) {
		status = set_port_feature(hub->hdev, port1, (warm ?
					USB_PORT_FEAT_BH_PORT_RESET :
					USB_PORT_FEAT_RESET));
		if (status == -ENODEV) {
			;	/* The hub is gone */
		} else if (status) {
			dev_err(&port_dev->dev,
					"cannot %sreset (err = %d)\n",
					warm ? "warm " : "", status);
		} else {
			status = hub_port_wait_reset(hub, port1, udev, delay,
								warm);
			if (status && status != -ENOTCONN && status != -ENODEV)
				dev_dbg(hub->intfdev,
						"port_wait_reset: err = %d\n",
						status);
		}

		/* Check for disconnect or reset */
		if (status == 0 || status == -ENOTCONN || status == -ENODEV) {
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_RESET);

			if (!hub_is_superspeed(hub->hdev))
				goto done;

			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_BH_PORT_RESET);
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_PORT_LINK_STATE);

			if (udev)
				usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);

			/*
			 * If a USB 3.0 device migrates from reset to an error
			 * state, re-issue the warm reset.
			 */
			if (hub_port_status(hub, port1,
					&portstatus, &portchange) < 0)
				goto done;

			if (!hub_port_warm_reset_required(hub, port1,
					portstatus))
				goto done;

			/*
			 * If the port is in SS.Inactive or Compliance Mode, the
			 * hot or warm reset failed.  Try another warm reset.
			 */
			if (!warm) {
				dev_dbg(&port_dev->dev,
						"hot reset failed, warm reset\n");
				warm = true;
			}
		}

		dev_dbg(&port_dev->dev,
				"not enabled, trying %sreset again...\n",
				warm ? "warm " : "");
		delay = HUB_LONG_RESET_TIME;
	}

	dev_err(&port_dev->dev, "Cannot enable. Maybe the USB cable is bad?\n");

done:
	if (status == 0) {
		if (port_dev->quirks & USB_PORT_QUIRK_FAST_ENUM)
			usleep_range(10000, 12000);
		else {
			/* TRSTRCY = 10 ms; plus some extra */
			reset_recovery_time = 10 + 40;

			/* Hub needs extra delay after resetting its port. */
			if (hub->hdev->quirks & USB_QUIRK_HUB_SLOW_RESET)
				reset_recovery_time += 100;

			msleep(reset_recovery_time);
		}

		if (udev) {
			struct usb_hcd *hcd = bus_to_hcd(udev->bus);

			update_devnum(udev, 0);
			/* The xHC may think the device is already reset,
			 * so ignore the status.
			 */
			if (hcd->driver->reset_device)
				hcd->driver->reset_device(hcd, udev);

			usb_set_device_state(udev, USB_STATE_DEFAULT);
		}
	} else {
		if (udev)
			usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	}

	if (!hub_is_superspeed(hub->hdev))
		up_read(&ehci_cf_port_reset_rwsem);

	return status;
}