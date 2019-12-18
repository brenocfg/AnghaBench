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
struct urb {scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  status; } ;
struct fhci_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EREMOTEIO ; 
 int URB_SHORT_NOT_OK ; 
 int /*<<< orphan*/  fhci_to_hcd (struct fhci_hcd*) ; 
 int /*<<< orphan*/  free_urb_priv (struct fhci_hcd*,struct urb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 

void fhci_urb_complete_free(struct fhci_hcd *fhci, struct urb *urb)
{
	free_urb_priv(fhci, urb);

	if (urb->status == -EINPROGRESS) {
		if (urb->actual_length != urb->transfer_buffer_length &&
				urb->transfer_flags & URB_SHORT_NOT_OK)
			urb->status = -EREMOTEIO;
		else
			urb->status = 0;
	}

	usb_hcd_unlink_urb_from_ep(fhci_to_hcd(fhci), urb);

	spin_unlock(&fhci->lock);

	usb_hcd_giveback_urb(fhci_to_hcd(fhci), urb, urb->status);

	spin_lock(&fhci->lock);
}