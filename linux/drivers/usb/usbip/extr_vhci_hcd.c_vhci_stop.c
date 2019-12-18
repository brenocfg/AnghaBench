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
struct vhci_hcd {struct vhci_device* vdev; } ;
struct vhci_device {int /*<<< orphan*/  ud; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_EVENT_REMOVED ; 
 int VHCI_HC_PORTS ; 
 TYPE_1__* hcd_dev (struct usb_hcd*) ; 
 int /*<<< orphan*/  hcd_name (struct usb_hcd*) ; 
 int hcd_name_to_id (int /*<<< orphan*/ ) ; 
 struct vhci_hcd* hcd_to_vhci_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_stop_eh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhci_attr_group ; 
 int /*<<< orphan*/  vhci_finish_attr_group () ; 

__attribute__((used)) static void vhci_stop(struct usb_hcd *hcd)
{
	struct vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	int id, rhport;

	usbip_dbg_vhci_hc("stop VHCI controller\n");

	/* 1. remove the userland interface of vhci_hcd */
	id = hcd_name_to_id(hcd_name(hcd));
	if (id == 0 && usb_hcd_is_primary_hcd(hcd)) {
		sysfs_remove_group(&hcd_dev(hcd)->kobj, &vhci_attr_group);
		vhci_finish_attr_group();
	}

	/* 2. shutdown all the ports of vhci_hcd */
	for (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) {
		struct vhci_device *vdev = &vhci_hcd->vdev[rhport];

		usbip_event_add(&vdev->ud, VDEV_EVENT_REMOVED);
		usbip_stop_eh(&vdev->ud);
	}
}