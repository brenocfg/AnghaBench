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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_CONTEXT_ADDRESS ; 
 int xhci_setup_device (struct usb_hcd*,struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_address_device(struct usb_hcd *hcd, struct usb_device *udev)
{
	return xhci_setup_device(hcd, udev, SETUP_CONTEXT_ADDRESS);
}