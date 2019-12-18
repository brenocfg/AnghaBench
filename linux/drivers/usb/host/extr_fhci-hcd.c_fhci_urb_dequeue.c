#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct urb_priv {scalar_t__ state; TYPE_2__* ed; } ;
struct urb {struct urb_priv* hcpriv; TYPE_1__* dev; } ;
struct fhci_usb {scalar_t__ port_status; } ;
struct fhci_hcd {int /*<<< orphan*/  lock; struct fhci_usb* usb_lld; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FHCI_ED_URB_DEL ; 
 scalar_t__ FHCI_PORT_DISABLED ; 
 scalar_t__ URB_DEL ; 
 int /*<<< orphan*/  fhci_urb_complete_free (struct fhci_hcd*,struct urb*) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 

__attribute__((used)) static int fhci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);
	struct fhci_usb *usb = fhci->usb_lld;
	int ret = -EINVAL;
	unsigned long flags;

	if (!urb || !urb->dev || !urb->dev->bus)
		goto out;

	spin_lock_irqsave(&fhci->lock, flags);

	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (ret)
		goto out2;

	if (usb->port_status != FHCI_PORT_DISABLED) {
		struct urb_priv *urb_priv;

		/*
		 * flag the urb's data for deletion in some upcoming
		 * SF interrupt's delete list processing
		 */
		urb_priv = urb->hcpriv;

		if (!urb_priv || (urb_priv->state == URB_DEL))
			goto out2;

		urb_priv->state = URB_DEL;

		/* already pending? */
		urb_priv->ed->state = FHCI_ED_URB_DEL;
	} else {
		fhci_urb_complete_free(fhci, urb);
	}

out2:
	spin_unlock_irqrestore(&fhci->lock, flags);
out:
	return ret;
}