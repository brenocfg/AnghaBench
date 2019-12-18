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
struct vhci_priv {int seqnum; int /*<<< orphan*/  list; struct urb* urb; struct vhci_device* vdev; } ;
struct vhci_hcd {int /*<<< orphan*/  seqnum; } ;
struct vhci_device {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  priv_tx; int /*<<< orphan*/  ud; } ;
struct urb {void* hcpriv; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct vhci_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vhci_hcd* vdev_to_vhci_hcd (struct vhci_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhci_tx_urb(struct urb *urb, struct vhci_device *vdev)
{
	struct vhci_priv *priv;
	struct vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	unsigned long flags;

	priv = kzalloc(sizeof(struct vhci_priv), GFP_ATOMIC);
	if (!priv) {
		usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
		return;
	}

	spin_lock_irqsave(&vdev->priv_lock, flags);

	priv->seqnum = atomic_inc_return(&vhci_hcd->seqnum);
	if (priv->seqnum == 0xffff)
		dev_info(&urb->dev->dev, "seqnum max\n");

	priv->vdev = vdev;
	priv->urb = urb;

	urb->hcpriv = (void *) priv;

	list_add_tail(&priv->list, &vdev->priv_tx);

	wake_up(&vdev->waitq_tx);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);
}