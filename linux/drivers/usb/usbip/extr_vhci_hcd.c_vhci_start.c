#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vhci_hcd {int /*<<< orphan*/  seqnum; struct vhci_device* vdev; TYPE_1__* vhci; } ;
struct vhci_device {int rhport; } ;
struct TYPE_6__ {int otg_port; } ;
struct usb_hcd {int uses_new_polling; TYPE_2__ self; scalar_t__ power_budget; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int VHCI_HC_PORTS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 TYPE_3__* hcd_dev (struct usb_hcd*) ; 
 int /*<<< orphan*/  hcd_name (struct usb_hcd*) ; 
 int hcd_name_to_id (int /*<<< orphan*/ ) ; 
 struct vhci_hcd* hcd_to_vhci_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  vhci_attr_group ; 
 int /*<<< orphan*/  vhci_device_init (struct vhci_device*) ; 
 int /*<<< orphan*/  vhci_finish_attr_group () ; 
 int vhci_init_attr_group () ; 

__attribute__((used)) static int vhci_start(struct usb_hcd *hcd)
{
	struct vhci_hcd *vhci_hcd = hcd_to_vhci_hcd(hcd);
	int id, rhport;
	int err;

	usbip_dbg_vhci_hc("enter vhci_start\n");

	if (usb_hcd_is_primary_hcd(hcd))
		spin_lock_init(&vhci_hcd->vhci->lock);

	/* initialize private data of usb_hcd */

	for (rhport = 0; rhport < VHCI_HC_PORTS; rhport++) {
		struct vhci_device *vdev = &vhci_hcd->vdev[rhport];

		vhci_device_init(vdev);
		vdev->rhport = rhport;
	}

	atomic_set(&vhci_hcd->seqnum, 0);

	hcd->power_budget = 0; /* no limit */
	hcd->uses_new_polling = 1;

#ifdef CONFIG_USB_OTG
	hcd->self.otg_port = 1;
#endif

	id = hcd_name_to_id(hcd_name(hcd));
	if (id < 0) {
		pr_err("invalid vhci name %s\n", hcd_name(hcd));
		return -EINVAL;
	}

	/* vhci_hcd is now ready to be controlled through sysfs */
	if (id == 0 && usb_hcd_is_primary_hcd(hcd)) {
		err = vhci_init_attr_group();
		if (err) {
			dev_err(hcd_dev(hcd), "init attr group failed, err = %d\n", err);
			return err;
		}
		err = sysfs_create_group(&hcd_dev(hcd)->kobj, &vhci_attr_group);
		if (err) {
			dev_err(hcd_dev(hcd), "create sysfs files failed, err = %d\n", err);
			vhci_finish_attr_group();
			return err;
		}
		pr_info("created sysfs %s\n", hcd_name(hcd));
	}

	return 0;
}