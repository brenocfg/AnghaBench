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
struct usb_qualifier_descriptor {int dummy; } ;
struct usb_hub {int /*<<< orphan*/  leds; int /*<<< orphan*/ * indicator; scalar_t__ has_indicators; } ;
struct usb_device {int quirks; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDICATOR_GREEN_BLINK ; 
 int /*<<< orphan*/  USB_DT_DEVICE_QUALIFIER ; 
 int USB_QUIRK_DEVICE_QUALIFIER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_qualifier_descriptor*) ; 
 struct usb_qualifier_descriptor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int usb_get_descriptor (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_qualifier_descriptor*,int) ; 

__attribute__((used)) static void
check_highspeed(struct usb_hub *hub, struct usb_device *udev, int port1)
{
	struct usb_qualifier_descriptor	*qual;
	int				status;

	if (udev->quirks & USB_QUIRK_DEVICE_QUALIFIER)
		return;

	qual = kmalloc(sizeof *qual, GFP_KERNEL);
	if (qual == NULL)
		return;

	status = usb_get_descriptor(udev, USB_DT_DEVICE_QUALIFIER, 0,
			qual, sizeof *qual);
	if (status == sizeof *qual) {
		dev_info(&udev->dev, "not running at top speed; "
			"connect to a high speed hub\n");
		/* hub LEDs are probably harder to miss than syslog */
		if (hub->has_indicators) {
			hub->indicator[port1-1] = INDICATOR_GREEN_BLINK;
			queue_delayed_work(system_power_efficient_wq,
					&hub->leds, 0);
		}
	}
	kfree(qual);
}