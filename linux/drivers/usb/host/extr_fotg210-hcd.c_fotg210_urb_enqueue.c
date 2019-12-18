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
struct usb_hcd {int dummy; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/  pipe; } ;
struct list_head {int dummy; } ;
struct fotg210_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int intr_submit (struct fotg210_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int itd_submit (struct fotg210_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qh_urb_transaction (struct fotg210_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int submit_async (struct fotg210_hcd*,struct urb*,struct list_head*,int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fotg210_urb_enqueue(struct usb_hcd *hcd, struct urb *urb,
		gfp_t mem_flags)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	struct list_head qtd_list;

	INIT_LIST_HEAD(&qtd_list);

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
		/* qh_completions() code doesn't handle all the fault cases
		 * in multi-TD control transfers.  Even 1KB is rare anyway.
		 */
		if (urb->transfer_buffer_length > (16 * 1024))
			return -EMSGSIZE;
		/* FALLTHROUGH */
	/* case PIPE_BULK: */
	default:
		if (!qh_urb_transaction(fotg210, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return submit_async(fotg210, urb, &qtd_list, mem_flags);

	case PIPE_INTERRUPT:
		if (!qh_urb_transaction(fotg210, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return intr_submit(fotg210, urb, &qtd_list, mem_flags);

	case PIPE_ISOCHRONOUS:
		return itd_submit(fotg210, urb, mem_flags);
	}
}