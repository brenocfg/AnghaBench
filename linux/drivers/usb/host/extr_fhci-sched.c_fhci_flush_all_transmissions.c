#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct td {struct packet* pkt; } ;
struct packet {int /*<<< orphan*/  status; } ;
struct fhci_usb {TYPE_2__* fhci; TYPE_3__* actual_frame; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_status; } ;
struct TYPE_5__ {TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  usb_usmod; int /*<<< orphan*/  usb_usber; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_END_TRANSMISSION ; 
 int USB_MODE_EN ; 
 int /*<<< orphan*/  USB_TD_TX_ER_TIMEOUT ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fhci_flush_bds (struct fhci_usb*) ; 
 struct td* fhci_peek_td_from_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  fhci_transaction_confirm (struct fhci_usb*,struct packet*) ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 

void fhci_flush_all_transmissions(struct fhci_usb *usb)
{
	u8 mode;
	struct td *td;

	mode = in_8(&usb->fhci->regs->usb_usmod);
	clrbits8(&usb->fhci->regs->usb_usmod, USB_MODE_EN);

	fhci_flush_bds(usb);

	while ((td = fhci_peek_td_from_frame(usb->actual_frame)) != NULL) {
		struct packet *pkt = td->pkt;

		pkt->status = USB_TD_TX_ER_TIMEOUT;
		fhci_transaction_confirm(usb, pkt);
	}

	usb->actual_frame->frame_status = FRAME_END_TRANSMISSION;

	/* reset the event register */
	out_be16(&usb->fhci->regs->usb_usber, 0xffff);
	/* enable the USB controller */
	out_8(&usb->fhci->regs->usb_usmod, mode | USB_MODE_EN);
}