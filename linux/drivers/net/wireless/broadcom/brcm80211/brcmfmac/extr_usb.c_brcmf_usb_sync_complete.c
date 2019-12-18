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
struct urb {scalar_t__ context; } ;
struct brcmf_usbdev_info {int ctl_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_usb_ioctl_resp_wake (struct brcmf_usbdev_info*) ; 

__attribute__((used)) static void
brcmf_usb_sync_complete(struct urb *urb)
{
	struct brcmf_usbdev_info *devinfo =
			(struct brcmf_usbdev_info *)urb->context;

	devinfo->ctl_completed = true;
	brcmf_usb_ioctl_resp_wake(devinfo);
}