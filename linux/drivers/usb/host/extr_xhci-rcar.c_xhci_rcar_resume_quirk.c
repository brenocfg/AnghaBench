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
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int xhci_rcar_download_firmware (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_rcar_start (struct usb_hcd*) ; 

int xhci_rcar_resume_quirk(struct usb_hcd *hcd)
{
	int ret;

	ret = xhci_rcar_download_firmware(hcd);
	if (!ret)
		xhci_rcar_start(hcd);

	return ret;
}