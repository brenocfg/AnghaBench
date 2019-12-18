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
struct usb_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct brcmf_usbdev_info {scalar_t__ wowl_enabled; TYPE_1__ bus_pub; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMFMAC_USB_STATE_SLEEP ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_cancel_all_urbs (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_free (int /*<<< orphan*/ *) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 

__attribute__((used)) static int brcmf_usb_suspend(struct usb_interface *intf, pm_message_t state)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);

	brcmf_dbg(USB, "Enter\n");
	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_SLEEP;
	if (devinfo->wowl_enabled) {
		brcmf_cancel_all_urbs(devinfo);
	} else {
		brcmf_detach(&usb->dev);
		brcmf_free(&usb->dev);
	}
	return 0;
}