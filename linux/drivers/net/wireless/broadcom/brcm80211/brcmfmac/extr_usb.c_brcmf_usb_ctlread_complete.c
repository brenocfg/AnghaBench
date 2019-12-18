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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; scalar_t__ context; } ;
struct brcmf_usbdev_info {int /*<<< orphan*/  ctl_urb_actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_USB_CBCTL_READ ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_usb_ctl_complete (struct brcmf_usbdev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_usb_ctlread_complete(struct urb *urb)
{
	struct brcmf_usbdev_info *devinfo =
		(struct brcmf_usbdev_info *)urb->context;

	brcmf_dbg(USB, "Enter\n");
	devinfo->ctl_urb_actual_length = urb->actual_length;
	brcmf_usb_ctl_complete(devinfo, BRCMF_USB_CBCTL_READ,
		urb->status);
}