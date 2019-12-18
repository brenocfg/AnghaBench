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
struct vhci_hcd {int /*<<< orphan*/  seqnum; struct vhci* vhci; } ;
struct usbip_device {int dummy; } ;
struct vhci_device {int /*<<< orphan*/  priv_lock; struct usbip_device ud; } ;
struct vhci {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_1__ base; } ;
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_flags; scalar_t__ num_sgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_DMA_MAP_SG ; 
 int /*<<< orphan*/  USBIP_RET_SUBMIT ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_TCP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct urb* pickup_urb_and_free_priv (struct vhci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 scalar_t__ usbip_dbg_flag_vhci_rx ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rx (char*,...) ; 
 int /*<<< orphan*/  usbip_dump_urb (struct urb*) ; 
 int /*<<< orphan*/  usbip_event_add (struct usbip_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pack_pdu (struct usbip_header*,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pad_iso (struct usbip_device*,struct urb*) ; 
 scalar_t__ usbip_recv_iso (struct usbip_device*,struct urb*) ; 
 scalar_t__ usbip_recv_xbuff (struct usbip_device*,struct urb*) ; 
 struct vhci_hcd* vdev_to_vhci_hcd (struct vhci_device*) ; 
 int /*<<< orphan*/  vhci_hcd_to_hcd (struct vhci_hcd*) ; 

__attribute__((used)) static void vhci_recv_ret_submit(struct vhci_device *vdev,
				 struct usbip_header *pdu)
{
	struct vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	struct vhci *vhci = vhci_hcd->vhci;
	struct usbip_device *ud = &vdev->ud;
	struct urb *urb;
	unsigned long flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);
	urb = pickup_urb_and_free_priv(vdev, pdu->base.seqnum);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	if (!urb) {
		pr_err("cannot find a urb of seqnum %u max seqnum %d\n",
			pdu->base.seqnum,
			atomic_read(&vhci_hcd->seqnum));
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		return;
	}

	/* unpack the pdu to a urb */
	usbip_pack_pdu(pdu, urb, USBIP_RET_SUBMIT, 0);

	/* recv transfer buffer */
	if (usbip_recv_xbuff(ud, urb) < 0)
		return;

	/* recv iso_packet_descriptor */
	if (usbip_recv_iso(ud, urb) < 0)
		return;

	/* restore the padding in iso packets */
	usbip_pad_iso(ud, urb);

	if (usbip_dbg_flag_vhci_rx)
		usbip_dump_urb(urb);

	if (urb->num_sgs)
		urb->transfer_flags &= ~URB_DMA_MAP_SG;

	usbip_dbg_vhci_rx("now giveback urb %u\n", pdu->base.seqnum);

	spin_lock_irqsave(&vhci->lock, flags);
	usb_hcd_unlink_urb_from_ep(vhci_hcd_to_hcd(vhci_hcd), urb);
	spin_unlock_irqrestore(&vhci->lock, flags);

	usb_hcd_giveback_urb(vhci_hcd_to_hcd(vhci_hcd), urb, urb->status);

	usbip_dbg_vhci_rx("Leave\n");
}