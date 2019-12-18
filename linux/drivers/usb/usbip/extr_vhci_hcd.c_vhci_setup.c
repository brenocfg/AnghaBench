#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vhci {TYPE_2__* vhci_hcd_ss; TYPE_1__* vhci_hcd_hs; } ;
struct TYPE_8__ {int sg_tablesize; int no_sg_constraint; TYPE_3__* root_hub; int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_4__ self; int /*<<< orphan*/  speed; } ;
struct TYPE_7__ {int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {struct vhci* vhci; } ;
struct TYPE_5__ {struct vhci* vhci; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_USB2 ; 
 int /*<<< orphan*/  HCD_USB3 ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ ) ; 
 void* hcd_to_vhci_hcd (struct usb_hcd*) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int vhci_setup(struct usb_hcd *hcd)
{
	struct vhci *vhci = *((void **)dev_get_platdata(hcd->self.controller));
	if (usb_hcd_is_primary_hcd(hcd)) {
		vhci->vhci_hcd_hs = hcd_to_vhci_hcd(hcd);
		vhci->vhci_hcd_hs->vhci = vhci;
		/*
		 * Mark the first roothub as being USB 2.0.
		 * The USB 3.0 roothub will be registered later by
		 * vhci_hcd_probe()
		 */
		hcd->speed = HCD_USB2;
		hcd->self.root_hub->speed = USB_SPEED_HIGH;
	} else {
		vhci->vhci_hcd_ss = hcd_to_vhci_hcd(hcd);
		vhci->vhci_hcd_ss->vhci = vhci;
		hcd->speed = HCD_USB3;
		hcd->self.root_hub->speed = USB_SPEED_SUPER;
	}

	/*
	 * Support SG.
	 * sg_tablesize is an arbitrary value to alleviate memory pressure
	 * on the host.
	 */
	hcd->self.sg_tablesize = 32;
	hcd->self.no_sg_constraint = 1;

	return 0;
}