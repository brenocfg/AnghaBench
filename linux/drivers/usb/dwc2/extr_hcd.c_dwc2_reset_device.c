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
struct usb_hcd {int dummy; } ;
struct usb_device {scalar_t__ speed; } ;
struct TYPE_2__ {int /*<<< orphan*/  change_speed_quirk; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPRT0_SPD_FULL_SPEED ; 
 int /*<<< orphan*/  HPRT0_SPD_HIGH_SPEED ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_change_bus_speed (struct usb_hcd*,int /*<<< orphan*/ ) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 

__attribute__((used)) static int dwc2_reset_device(struct usb_hcd *hcd, struct usb_device *udev)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	if (!hsotg->params.change_speed_quirk)
		return 0;

	if (udev->speed == USB_SPEED_HIGH) {
		dev_info(hsotg->dev, "Set speed to high-speed\n");
		dwc2_change_bus_speed(hcd, HPRT0_SPD_HIGH_SPEED);
	} else if ((udev->speed == USB_SPEED_FULL ||
				udev->speed == USB_SPEED_LOW)) {
		/*
		 * Change speed setting to full-speed if there's
		 * a full-speed or low-speed device plugged in.
		 */
		dev_info(hsotg->dev, "Set speed to full-speed\n");
		dwc2_change_bus_speed(hcd, HPRT0_SPD_FULL_SPEED);
	}

	return 0;
}