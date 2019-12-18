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
struct usb_hcd {int dummy; } ;
struct fhci_usb {int /*<<< orphan*/  ep0; TYPE_1__* actual_frame; } ;
struct fhci_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; struct fhci_usb* usb_lld; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ frame_status; } ;

/* Variables and functions */
 scalar_t__ FRAME_IS_TRANSMITTED ; 
 scalar_t__ FRAME_TIMER_END_TRANSMISSION ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  fhci_push_dummy_bd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_schedule_transactions (struct fhci_usb*) ; 
 int /*<<< orphan*/  gtm_set_exact_timer16 (int /*<<< orphan*/ ,int,int) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

irqreturn_t fhci_frame_limit_timer_irq(int irq, void *_hcd)
{
	struct usb_hcd *hcd = _hcd;
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);
	struct fhci_usb *usb = fhci->usb_lld;

	spin_lock(&fhci->lock);

	gtm_set_exact_timer16(fhci->timer, 1000, false);

	if (usb->actual_frame->frame_status == FRAME_IS_TRANSMITTED) {
		usb->actual_frame->frame_status = FRAME_TIMER_END_TRANSMISSION;
		fhci_push_dummy_bd(usb->ep0);
	}

	fhci_schedule_transactions(usb);

	spin_unlock(&fhci->lock);

	return IRQ_HANDLED;
}