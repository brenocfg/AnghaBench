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
struct brcmf_usbdev_info {scalar_t__ settings; int /*<<< orphan*/  rx_reqs; int /*<<< orphan*/  tx_reqs; int /*<<< orphan*/  bulk_urb; int /*<<< orphan*/  ctl_urb; int /*<<< orphan*/  tx_freeq; int /*<<< orphan*/  rx_freeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_release_module_param (scalar_t__) ; 
 int /*<<< orphan*/  brcmf_usb_free_q (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_usb_detach(struct brcmf_usbdev_info *devinfo)
{
	brcmf_dbg(USB, "Enter, devinfo %p\n", devinfo);

	/* free the URBS */
	brcmf_usb_free_q(&devinfo->rx_freeq);
	brcmf_usb_free_q(&devinfo->tx_freeq);

	usb_free_urb(devinfo->ctl_urb);
	usb_free_urb(devinfo->bulk_urb);

	kfree(devinfo->tx_reqs);
	kfree(devinfo->rx_reqs);

	if (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);
}