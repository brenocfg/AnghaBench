#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_port {int /*<<< orphan*/  dev; struct usb_device* child; int /*<<< orphan*/  port_owner; } ;
struct usb_hub {unsigned int mA_per_port; struct usb_device* hdev; int /*<<< orphan*/ * intfdev; int /*<<< orphan*/  leds; int /*<<< orphan*/ * indicator; scalar_t__ has_indicators; int /*<<< orphan*/  removed_bits; struct usb_port** ports; } ;
struct usb_hcd {TYPE_1__* driver; scalar_t__ usb_phy; } ;
struct TYPE_4__ {scalar_t__ bDeviceClass; int /*<<< orphan*/  bcdUSB; } ;
struct usb_device {scalar_t__ speed; unsigned int bus_mA; scalar_t__ devnum; int quirks; scalar_t__ state; scalar_t__ parent; TYPE_2__ descriptor; int /*<<< orphan*/  dev; int /*<<< orphan*/  wusb; scalar_t__ level; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* relinquish_port ) (struct usb_hcd*,int) ;int /*<<< orphan*/  (* port_handed_over ) (struct usb_hcd*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  INDICATOR_AMBER_BLINK ; 
 int SET_CONFIG_TRIES ; 
 scalar_t__ USB_CLASS_HUB ; 
 int USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_C_ENABLE ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_QUIRK_DELAY_INIT ; 
 int /*<<< orphan*/  USB_RECIP_DEVICE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  USB_STATE_POWERED ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_highspeed (struct usb_hub*,struct usb_device*,int) ; 
 int /*<<< orphan*/  choose_devnum (struct usb_device*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_state_lock ; 
 scalar_t__ highspeed_hubs ; 
 int /*<<< orphan*/  hub_free_dev (struct usb_device*) ; 
 scalar_t__ hub_is_port_power_switchable (struct usb_hub*) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int /*<<< orphan*/  hub_is_wusb (struct usb_hub*) ; 
 int hub_port_debounce_be_stable (struct usb_hub*,int) ; 
 int /*<<< orphan*/  hub_port_disable (struct usb_hub*,int,int) ; 
 int hub_port_init (struct usb_hub*,struct usb_device*,int,int) ; 
 int hub_power_on_good_delay (struct usb_hub*) ; 
 int hub_power_remaining (struct usb_hub*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_is_power_on (struct usb_hub*,int) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_devnum (struct usb_device*) ; 
 int /*<<< orphan*/  set_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,int) ; 
 int /*<<< orphan*/  stub2 (struct usb_hcd*,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 struct usb_device* usb_alloc_dev (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_disconnect (struct usb_device**) ; 
 int /*<<< orphan*/  usb_ep0_reinit (struct usb_device*) ; 
 int usb_get_std_status (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usb_hub_set_port_power (struct usb_device*,struct usb_hub*,int,int) ; 
 int /*<<< orphan*/  usb_lock_port (struct usb_port*) ; 
 int usb_new_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_phy_notify_connect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_phy_notify_disconnect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_port_peer_mutex ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_port (struct usb_port*) ; 

__attribute__((used)) static void hub_port_connect(struct usb_hub *hub, int port1, u16 portstatus,
		u16 portchange)
{
	int status = -ENODEV;
	int i;
	unsigned unit_load;
	struct usb_device *hdev = hub->hdev;
	struct usb_hcd *hcd = bus_to_hcd(hdev->bus);
	struct usb_port *port_dev = hub->ports[port1 - 1];
	struct usb_device *udev = port_dev->child;
	static int unreliable_port = -1;

	/* Disconnect any existing devices under this port */
	if (udev) {
		if (hcd->usb_phy && !hdev->parent)
			usb_phy_notify_disconnect(hcd->usb_phy, udev->speed);
		usb_disconnect(&port_dev->child);
	}

	/* We can forget about a "removed" device when there's a physical
	 * disconnect or the connect status changes.
	 */
	if (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			(portchange & USB_PORT_STAT_C_CONNECTION))
		clear_bit(port1, hub->removed_bits);

	if (portchange & (USB_PORT_STAT_C_CONNECTION |
				USB_PORT_STAT_C_ENABLE)) {
		status = hub_port_debounce_be_stable(hub, port1);
		if (status < 0) {
			if (status != -ENODEV &&
				port1 != unreliable_port &&
				printk_ratelimit())
				dev_err(&port_dev->dev, "connect-debounce failed\n");
			portstatus &= ~USB_PORT_STAT_CONNECTION;
			unreliable_port = port1;
		} else {
			portstatus = status;
		}
	}

	/* Return now if debouncing failed or nothing is connected or
	 * the device was "removed".
	 */
	if (!(portstatus & USB_PORT_STAT_CONNECTION) ||
			test_bit(port1, hub->removed_bits)) {

		/*
		 * maybe switch power back on (e.g. root hub was reset)
		 * but only if the port isn't owned by someone else.
		 */
		if (hub_is_port_power_switchable(hub)
				&& !port_is_power_on(hub, portstatus)
				&& !port_dev->port_owner)
			set_port_feature(hdev, port1, USB_PORT_FEAT_POWER);

		if (portstatus & USB_PORT_STAT_ENABLE)
			goto done;
		return;
	}
	if (hub_is_superspeed(hub->hdev))
		unit_load = 150;
	else
		unit_load = 100;

	status = 0;
	for (i = 0; i < SET_CONFIG_TRIES; i++) {

		/* reallocate for each attempt, since references
		 * to the previous one can escape in various ways
		 */
		udev = usb_alloc_dev(hdev, hdev->bus, port1);
		if (!udev) {
			dev_err(&port_dev->dev,
					"couldn't allocate usb_device\n");
			goto done;
		}

		usb_set_device_state(udev, USB_STATE_POWERED);
		udev->bus_mA = hub->mA_per_port;
		udev->level = hdev->level + 1;
		udev->wusb = hub_is_wusb(hub);

		/* Devices connected to SuperSpeed hubs are USB 3.0 or later */
		if (hub_is_superspeed(hub->hdev))
			udev->speed = USB_SPEED_SUPER;
		else
			udev->speed = USB_SPEED_UNKNOWN;

		choose_devnum(udev);
		if (udev->devnum <= 0) {
			status = -ENOTCONN;	/* Don't retry */
			goto loop;
		}

		/* reset (non-USB 3.0 devices) and get descriptor */
		usb_lock_port(port_dev);
		status = hub_port_init(hub, udev, port1, i);
		usb_unlock_port(port_dev);
		if (status < 0)
			goto loop;

		if (udev->quirks & USB_QUIRK_DELAY_INIT)
			msleep(2000);

		/* consecutive bus-powered hubs aren't reliable; they can
		 * violate the voltage drop budget.  if the new child has
		 * a "powered" LED, users should notice we didn't enable it
		 * (without reading syslog), even without per-port LEDs
		 * on the parent.
		 */
		if (udev->descriptor.bDeviceClass == USB_CLASS_HUB
				&& udev->bus_mA <= unit_load) {
			u16	devstat;

			status = usb_get_std_status(udev, USB_RECIP_DEVICE, 0,
					&devstat);
			if (status) {
				dev_dbg(&udev->dev, "get status %d ?\n", status);
				goto loop_disable;
			}
			if ((devstat & (1 << USB_DEVICE_SELF_POWERED)) == 0) {
				dev_err(&udev->dev,
					"can't connect bus-powered hub "
					"to this port\n");
				if (hub->has_indicators) {
					hub->indicator[port1-1] =
						INDICATOR_AMBER_BLINK;
					queue_delayed_work(
						system_power_efficient_wq,
						&hub->leds, 0);
				}
				status = -ENOTCONN;	/* Don't retry */
				goto loop_disable;
			}
		}

		/* check for devices running slower than they could */
		if (le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0200
				&& udev->speed == USB_SPEED_FULL
				&& highspeed_hubs != 0)
			check_highspeed(hub, udev, port1);

		/* Store the parent's children[] pointer.  At this point
		 * udev becomes globally accessible, although presumably
		 * no one will look at it until hdev is unlocked.
		 */
		status = 0;

		mutex_lock(&usb_port_peer_mutex);

		/* We mustn't add new devices if the parent hub has
		 * been disconnected; we would race with the
		 * recursively_mark_NOTATTACHED() routine.
		 */
		spin_lock_irq(&device_state_lock);
		if (hdev->state == USB_STATE_NOTATTACHED)
			status = -ENOTCONN;
		else
			port_dev->child = udev;
		spin_unlock_irq(&device_state_lock);
		mutex_unlock(&usb_port_peer_mutex);

		/* Run it through the hoops (find a driver, etc) */
		if (!status) {
			status = usb_new_device(udev);
			if (status) {
				mutex_lock(&usb_port_peer_mutex);
				spin_lock_irq(&device_state_lock);
				port_dev->child = NULL;
				spin_unlock_irq(&device_state_lock);
				mutex_unlock(&usb_port_peer_mutex);
			} else {
				if (hcd->usb_phy && !hdev->parent)
					usb_phy_notify_connect(hcd->usb_phy,
							udev->speed);
			}
		}

		if (status)
			goto loop_disable;

		status = hub_power_remaining(hub);
		if (status)
			dev_dbg(hub->intfdev, "%dmA power budget left\n", status);

		return;

loop_disable:
		hub_port_disable(hub, port1, 1);
loop:
		usb_ep0_reinit(udev);
		release_devnum(udev);
		hub_free_dev(udev);
		usb_put_dev(udev);
		if ((status == -ENOTCONN) || (status == -ENOTSUPP))
			break;

		/* When halfway through our retry count, power-cycle the port */
		if (i == (SET_CONFIG_TRIES / 2) - 1) {
			dev_info(&port_dev->dev, "attempt power cycle\n");
			usb_hub_set_port_power(hdev, hub, port1, false);
			msleep(2 * hub_power_on_good_delay(hub));
			usb_hub_set_port_power(hdev, hub, port1, true);
			msleep(hub_power_on_good_delay(hub));
		}
	}
	if (hub->hdev->parent ||
			!hcd->driver->port_handed_over ||
			!(hcd->driver->port_handed_over)(hcd, port1)) {
		if (status != -ENOTCONN && status != -ENODEV)
			dev_err(&port_dev->dev,
					"unable to enumerate USB device\n");
	}

done:
	hub_port_disable(hub, port1, 1);
	if (hcd->driver->relinquish_port && !hub->hdev->parent) {
		if (status != -ENOTCONN && status != -ENODEV)
			hcd->driver->relinquish_port(hcd, port1);
	}
}