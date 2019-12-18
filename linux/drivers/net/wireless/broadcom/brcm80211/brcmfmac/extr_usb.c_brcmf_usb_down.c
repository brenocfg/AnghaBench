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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_USB_STATE_DOWN ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_cancel_all_urbs (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (struct device*) ; 
 int /*<<< orphan*/  brcmf_usb_state_change (struct brcmf_usbdev_info*,scalar_t__) ; 

__attribute__((used)) static void brcmf_usb_down(struct device *dev)
{
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);

	brcmf_dbg(USB, "Enter\n");
	if (devinfo == NULL)
		return;

	if (devinfo->bus_pub.state == BRCMFMAC_USB_STATE_DOWN)
		return;

	brcmf_usb_state_change(devinfo, BRCMFMAC_USB_STATE_DOWN);

	brcmf_cancel_all_urbs(devinfo);
}