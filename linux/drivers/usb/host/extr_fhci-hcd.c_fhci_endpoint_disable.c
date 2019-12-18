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
struct usb_host_endpoint {struct ed* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct td {int /*<<< orphan*/  urb; } ;
struct fhci_hcd {int /*<<< orphan*/  lock; } ;
struct ed {int /*<<< orphan*/ * td_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  fhci_recycle_empty_ed (struct fhci_hcd*,struct ed*) ; 
 struct td* fhci_remove_td_from_ed (struct ed*) ; 
 int /*<<< orphan*/  fhci_urb_complete_free (struct fhci_hcd*,int /*<<< orphan*/ ) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fhci_endpoint_disable(struct usb_hcd *hcd,
				  struct usb_host_endpoint *ep)
{
	struct fhci_hcd *fhci;
	struct ed *ed;
	unsigned long flags;

	fhci = hcd_to_fhci(hcd);
	spin_lock_irqsave(&fhci->lock, flags);
	ed = ep->hcpriv;
	if (ed) {
		while (ed->td_head != NULL) {
			struct td *td = fhci_remove_td_from_ed(ed);
			fhci_urb_complete_free(fhci, td->urb);
		}
		fhci_recycle_empty_ed(fhci, ed);
		ep->hcpriv = NULL;
	}
	spin_unlock_irqrestore(&fhci->lock, flags);
}