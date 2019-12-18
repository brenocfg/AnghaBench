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
struct urb {int transfer_buffer_length; TYPE_1__* dev; int /*<<< orphan*/  pipe; } ;
struct list_head {int dummy; } ;
struct ehci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int intr_submit (struct ehci_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int itd_submit (struct ehci_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qh_urb_transaction (struct ehci_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int sitd_submit (struct ehci_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int submit_async (struct ehci_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_urb_enqueue (
	struct usb_hcd	*hcd,
	struct urb	*urb,
	gfp_t		mem_flags
) {
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	struct list_head	qtd_list;

	INIT_LIST_HEAD (&qtd_list);

	switch (usb_pipetype (urb->pipe)) {
	case PIPE_CONTROL:
		/* qh_completions() code doesn't handle all the fault cases
		 * in multi-TD control transfers.  Even 1KB is rare anyway.
		 */
		if (urb->transfer_buffer_length > (16 * 1024))
			return -EMSGSIZE;
		/* FALLTHROUGH */
	/* case PIPE_BULK: */
	default:
		if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return submit_async(ehci, urb, &qtd_list, mem_flags);

	case PIPE_INTERRUPT:
		if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return intr_submit(ehci, urb, &qtd_list, mem_flags);

	case PIPE_ISOCHRONOUS:
		if (urb->dev->speed == USB_SPEED_HIGH)
			return itd_submit (ehci, urb, mem_flags);
		else
			return sitd_submit (ehci, urb, mem_flags);
	}
}