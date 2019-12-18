#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int needs_remote_wakeup; int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct usb_hub {int quirk_check_port_auto_suspend; int /*<<< orphan*/  irq_urb_retry; int /*<<< orphan*/  irq_urb_lock; int /*<<< orphan*/  events; int /*<<< orphan*/  init_work; int /*<<< orphan*/  leds; struct usb_device* hdev; int /*<<< orphan*/ * intfdev; int /*<<< orphan*/  kref; } ;
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct usb_device_id {int driver_info; } ;
struct TYPE_5__ {scalar_t__ autosuspend_delay; } ;
struct TYPE_7__ {TYPE_1__ power; } ;
struct usb_device {scalar_t__ level; scalar_t__ speed; scalar_t__ parent; int /*<<< orphan*/  bus; TYPE_3__ dev; } ;
struct hc_driver {scalar_t__ bus_resume; scalar_t__ bus_suspend; } ;
struct TYPE_8__ {struct hc_driver* driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int E2BIG ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HUB_QUIRK_CHECK_PORT_AUTOSUSPEND ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_TOPO_LEVEL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 TYPE_4__* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  highspeed_hubs ; 
 scalar_t__ hub_configure (struct usb_hub*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hub_descriptor_is_sane (struct usb_host_interface*) ; 
 int /*<<< orphan*/  hub_disconnect (struct usb_interface*) ; 
 int /*<<< orphan*/  hub_event ; 
 int /*<<< orphan*/  hub_retry_irq_urb ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct usb_hub* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_work ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_hub*) ; 

__attribute__((used)) static int hub_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_host_interface *desc;
	struct usb_device *hdev;
	struct usb_hub *hub;

	desc = intf->cur_altsetting;
	hdev = interface_to_usbdev(intf);

	/*
	 * Set default autosuspend delay as 0 to speedup bus suspend,
	 * based on the below considerations:
	 *
	 * - Unlike other drivers, the hub driver does not rely on the
	 *   autosuspend delay to provide enough time to handle a wakeup
	 *   event, and the submitted status URB is just to check future
	 *   change on hub downstream ports, so it is safe to do it.
	 *
	 * - The patch might cause one or more auto supend/resume for
	 *   below very rare devices when they are plugged into hub
	 *   first time:
	 *
	 *   	devices having trouble initializing, and disconnect
	 *   	themselves from the bus and then reconnect a second
	 *   	or so later
	 *
	 *   	devices just for downloading firmware, and disconnects
	 *   	themselves after completing it
	 *
	 *   For these quite rare devices, their drivers may change the
	 *   autosuspend delay of their parent hub in the probe() to one
	 *   appropriate value to avoid the subtle problem if someone
	 *   does care it.
	 *
	 * - The patch may cause one or more auto suspend/resume on
	 *   hub during running 'lsusb', but it is probably too
	 *   infrequent to worry about.
	 *
	 * - Change autosuspend delay of hub can avoid unnecessary auto
	 *   suspend timer for hub, also may decrease power consumption
	 *   of USB bus.
	 *
	 * - If user has indicated to prevent autosuspend by passing
	 *   usbcore.autosuspend = -1 then keep autosuspend disabled.
	 */
#ifdef CONFIG_PM
	if (hdev->dev.power.autosuspend_delay >= 0)
		pm_runtime_set_autosuspend_delay(&hdev->dev, 0);
#endif

	/*
	 * Hubs have proper suspend/resume support, except for root hubs
	 * where the controller driver doesn't have bus_suspend and
	 * bus_resume methods.
	 */
	if (hdev->parent) {		/* normal device */
		usb_enable_autosuspend(hdev);
	} else {			/* root hub */
		const struct hc_driver *drv = bus_to_hcd(hdev->bus)->driver;

		if (drv->bus_suspend && drv->bus_resume)
			usb_enable_autosuspend(hdev);
	}

	if (hdev->level == MAX_TOPO_LEVEL) {
		dev_err(&intf->dev,
			"Unsupported bus topology: hub nested too deep\n");
		return -E2BIG;
	}

#ifdef	CONFIG_USB_OTG_BLACKLIST_HUB
	if (hdev->parent) {
		dev_warn(&intf->dev, "ignoring external hub\n");
		return -ENODEV;
	}
#endif

	if (!hub_descriptor_is_sane(desc)) {
		dev_err(&intf->dev, "bad descriptor, ignoring hub\n");
		return -EIO;
	}

	/* We found a hub */
	dev_info(&intf->dev, "USB hub found\n");

	hub = kzalloc(sizeof(*hub), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;

	kref_init(&hub->kref);
	hub->intfdev = &intf->dev;
	hub->hdev = hdev;
	INIT_DELAYED_WORK(&hub->leds, led_work);
	INIT_DELAYED_WORK(&hub->init_work, NULL);
	INIT_WORK(&hub->events, hub_event);
	spin_lock_init(&hub->irq_urb_lock);
	timer_setup(&hub->irq_urb_retry, hub_retry_irq_urb, 0);
	usb_get_intf(intf);
	usb_get_dev(hdev);

	usb_set_intfdata(intf, hub);
	intf->needs_remote_wakeup = 1;
	pm_suspend_ignore_children(&intf->dev, true);

	if (hdev->speed == USB_SPEED_HIGH)
		highspeed_hubs++;

	if (id->driver_info & HUB_QUIRK_CHECK_PORT_AUTOSUSPEND)
		hub->quirk_check_port_auto_suspend = 1;

	if (hub_configure(hub, &desc->endpoint[0].desc) >= 0)
		return 0;

	hub_disconnect(intf);
	return -ENODEV;
}