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
typedef  size_t u8 ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; int /*<<< orphan*/  transfer_buffer_length; TYPE_1__* ep; } ;
struct max3421_hcd {int hien; int urb_done; int /*<<< orphan*/ * err_stat; struct urb* curr_urb; } ;
struct max3421_ep {int pkt_state; scalar_t__ retries; scalar_t__ naks; } ;
struct TYPE_2__ {struct max3421_ep* hcpriv; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX3421_HI_HXFRDN_BIT ; 
 int /*<<< orphan*/  MAX3421_HI_RCVDAV_BIT ; 
 size_t MAX3421_HRSL_OK ; 
 size_t MAX3421_HRSL_RESULT_MASK ; 
 int /*<<< orphan*/  MAX3421_REG_HRSL ; 
 int /*<<< orphan*/  PIPE_CONTROL ; 
#define  PKT_STATE_SETUP 130 
#define  PKT_STATE_TERMINATE 129 
#define  PKT_STATE_TRANSFER 128 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  max3421_handle_error (struct usb_hcd*,size_t) ; 
 int /*<<< orphan*/  max3421_next_transfer (struct usb_hcd*,int /*<<< orphan*/ ) ; 
 int max3421_transfer_in_done (struct usb_hcd*,struct urb*) ; 
 int max3421_transfer_out_done (struct usb_hcd*,struct urb*) ; 
 size_t spi_rd8 (struct usb_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_pipetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_urb_dir_in (struct urb*) ; 

__attribute__((used)) static void
max3421_host_transfer_done(struct usb_hcd *hcd)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	struct urb *urb = max3421_hcd->curr_urb;
	struct max3421_ep *max3421_ep;
	u8 result_code, hrsl;
	int urb_done = 0;

	max3421_hcd->hien &= ~(BIT(MAX3421_HI_HXFRDN_BIT) |
			       BIT(MAX3421_HI_RCVDAV_BIT));

	hrsl = spi_rd8(hcd, MAX3421_REG_HRSL);
	result_code = hrsl & MAX3421_HRSL_RESULT_MASK;

#ifdef DEBUG
	++max3421_hcd->err_stat[result_code];
#endif

	max3421_ep = urb->ep->hcpriv;

	if (unlikely(result_code != MAX3421_HRSL_OK)) {
		max3421_handle_error(hcd, hrsl);
		return;
	}

	max3421_ep->naks = 0;
	max3421_ep->retries = 0;
	switch (max3421_ep->pkt_state) {

	case PKT_STATE_SETUP:
		if (urb->transfer_buffer_length > 0)
			max3421_ep->pkt_state = PKT_STATE_TRANSFER;
		else
			max3421_ep->pkt_state = PKT_STATE_TERMINATE;
		break;

	case PKT_STATE_TRANSFER:
		if (usb_urb_dir_in(urb))
			urb_done = max3421_transfer_in_done(hcd, urb);
		else
			urb_done = max3421_transfer_out_done(hcd, urb);
		if (urb_done > 0 && usb_pipetype(urb->pipe) == PIPE_CONTROL) {
			/*
			 * We aren't really done - we still need to
			 * terminate the control transfer:
			 */
			max3421_hcd->urb_done = urb_done = 0;
			max3421_ep->pkt_state = PKT_STATE_TERMINATE;
		}
		break;

	case PKT_STATE_TERMINATE:
		urb_done = 1;
		break;
	}

	if (urb_done)
		max3421_hcd->urb_done = urb_done;
	else
		max3421_next_transfer(hcd, 0);
}