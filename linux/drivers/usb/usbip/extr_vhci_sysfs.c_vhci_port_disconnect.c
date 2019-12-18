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
struct vhci_hcd {struct vhci* vhci; struct vhci_device* vdev; } ;
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  lock; } ;
struct vhci_device {TYPE_1__ ud; } ;
struct vhci {int /*<<< orphan*/  lock; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VDEV_EVENT_DOWN ; 
 scalar_t__ VDEV_ST_NULL ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_sysfs (char*) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhci_port_disconnect(struct vhci_hcd *vhci_hcd, __u32 rhport)
{
	struct vhci_device *vdev = &vhci_hcd->vdev[rhport];
	struct vhci *vhci = vhci_hcd->vhci;
	unsigned long flags;

	usbip_dbg_vhci_sysfs("enter\n");

	/* lock */
	spin_lock_irqsave(&vhci->lock, flags);
	spin_lock(&vdev->ud.lock);

	if (vdev->ud.status == VDEV_ST_NULL) {
		pr_err("not connected %d\n", vdev->ud.status);

		/* unlock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&vhci->lock, flags);

		return -EINVAL;
	}

	/* unlock */
	spin_unlock(&vdev->ud.lock);
	spin_unlock_irqrestore(&vhci->lock, flags);

	usbip_event_add(&vdev->ud, VDEV_EVENT_DOWN);

	return 0;
}