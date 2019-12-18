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
struct xhci_hcd {int dummy; } ;
struct usb_hub_descriptor {int dummy; } ;
struct usb_hcd {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ HCD_USB3 ; 
 int /*<<< orphan*/  xhci_usb2_hub_descriptor (struct usb_hcd*,struct xhci_hcd*,struct usb_hub_descriptor*) ; 
 int /*<<< orphan*/  xhci_usb3_hub_descriptor (struct usb_hcd*,struct xhci_hcd*,struct usb_hub_descriptor*) ; 

__attribute__((used)) static void xhci_hub_descriptor(struct usb_hcd *hcd, struct xhci_hcd *xhci,
		struct usb_hub_descriptor *desc)
{

	if (hcd->speed >= HCD_USB3)
		xhci_usb3_hub_descriptor(hcd, xhci, desc);
	else
		xhci_usb2_hub_descriptor(hcd, xhci, desc);

}