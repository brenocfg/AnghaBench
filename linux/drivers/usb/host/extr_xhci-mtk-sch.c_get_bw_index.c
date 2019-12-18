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
struct xhci_virt_device {int real_port; } ;
struct TYPE_2__ {int num_ports; } ;
struct xhci_hcd {TYPE_1__ usb3_rhub; struct xhci_virt_device** devs; } ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {size_t slot_id; scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ usb_endpoint_dir_out (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_bw_index(struct xhci_hcd *xhci, struct usb_device *udev,
	struct usb_host_endpoint *ep)
{
	struct xhci_virt_device *virt_dev;
	int bw_index;

	virt_dev = xhci->devs[udev->slot_id];

	if (udev->speed >= USB_SPEED_SUPER) {
		if (usb_endpoint_dir_out(&ep->desc))
			bw_index = (virt_dev->real_port - 1) * 2;
		else
			bw_index = (virt_dev->real_port - 1) * 2 + 1;
	} else {
		/* add one more for each SS port */
		bw_index = virt_dev->real_port + xhci->usb3_rhub.num_ports - 1;
	}

	return bw_index;
}