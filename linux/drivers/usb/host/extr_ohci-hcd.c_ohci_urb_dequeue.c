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
struct TYPE_3__ {TYPE_2__* ed; } ;
typedef  TYPE_1__ urb_priv_t ;
struct usb_hcd {int dummy; } ;
struct urb {TYPE_1__* hcpriv; } ;
struct ohci_hcd {scalar_t__ rh_state; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ ED_OPER ; 
 scalar_t__ OHCI_RH_RUNNING ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_work (struct ohci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_ed_unlink (struct ohci_hcd*,TYPE_2__*) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 

__attribute__((used)) static int ohci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	unsigned long		flags;
	int			rc;
	urb_priv_t		*urb_priv;

	spin_lock_irqsave (&ohci->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc == 0) {

		/* Unless an IRQ completed the unlink while it was being
		 * handed to us, flag it for unlink and giveback, and force
		 * some upcoming INTR_SF to call finish_unlinks()
		 */
		urb_priv = urb->hcpriv;
		if (urb_priv->ed->state == ED_OPER)
			start_ed_unlink(ohci, urb_priv->ed);

		if (ohci->rh_state != OHCI_RH_RUNNING) {
			/* With HC dead, we can clean up right away */
			ohci_work(ohci);
		}
	}
	spin_unlock_irqrestore (&ohci->lock, flags);
	return rc;
}