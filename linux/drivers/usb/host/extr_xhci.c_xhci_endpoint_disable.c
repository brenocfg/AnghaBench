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
struct xhci_virt_ep {int ep_state; } ;
struct xhci_virt_device {struct xhci_virt_ep* eps; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; struct xhci_virt_device** devs; } ;
struct usb_host_endpoint {int /*<<< orphan*/ * hcpriv; int /*<<< orphan*/  desc; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {size_t slot_id; } ;

/* Variables and functions */
 int EP_CLEARING_TT ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int) ; 
 unsigned int xhci_get_endpoint_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_endpoint_disable(struct usb_hcd *hcd,
				  struct usb_host_endpoint *host_ep)
{
	struct xhci_hcd		*xhci;
	struct xhci_virt_device	*vdev;
	struct xhci_virt_ep	*ep;
	struct usb_device	*udev;
	unsigned long		flags;
	unsigned int		ep_index;

	xhci = hcd_to_xhci(hcd);
rescan:
	spin_lock_irqsave(&xhci->lock, flags);

	udev = (struct usb_device *)host_ep->hcpriv;
	if (!udev || !udev->slot_id)
		goto done;

	vdev = xhci->devs[udev->slot_id];
	if (!vdev)
		goto done;

	ep_index = xhci_get_endpoint_index(&host_ep->desc);
	ep = &vdev->eps[ep_index];
	if (!ep)
		goto done;

	/* wait for hub_tt_work to finish clearing hub TT */
	if (ep->ep_state & EP_CLEARING_TT) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		schedule_timeout_uninterruptible(1);
		goto rescan;
	}

	if (ep->ep_state)
		xhci_dbg(xhci, "endpoint disable with ep_state 0x%x\n",
			 ep->ep_state);
done:
	host_ep->hcpriv = NULL;
	spin_unlock_irqrestore(&xhci->lock, flags);
}