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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int host_perio_tx_fifo_size; } ;
struct dwc2_hsotg {TYPE_1__ params; } ;
struct dwc2_host_chan {scalar_t__ ep_type; int speed; TYPE_2__* qh; scalar_t__ xfer_len; int /*<<< orphan*/  do_split; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_active_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCCHAR_ODDFRM ; 
 int /*<<< orphan*/  HPTXSTS ; 
 int NS_TO_US (int) ; 
 int TXSTS_FSPCAVAIL_MASK ; 
 int TXSTS_FSPCAVAIL_SHIFT ; 
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dwc2_frame_num_dec (int,int) ; 
 scalar_t__ dwc2_frame_num_gt (int,int) ; 
 int dwc2_frame_num_inc (int /*<<< orphan*/ ,int) ; 
 int dwc2_hcd_get_future_frame_number (struct dwc2_hsotg*,int) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_sch_vdbg (struct dwc2_hsotg*,char*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int usb_calc_bus_time (int,int,int,scalar_t__) ; 

__attribute__((used)) static void dwc2_hc_set_even_odd_frame(struct dwc2_hsotg *hsotg,
				       struct dwc2_host_chan *chan, u32 *hcchar)
{
	if (chan->ep_type == USB_ENDPOINT_XFER_INT ||
	    chan->ep_type == USB_ENDPOINT_XFER_ISOC) {
		int host_speed;
		int xfer_ns;
		int xfer_us;
		int bytes_in_fifo;
		u16 fifo_space;
		u16 frame_number;
		u16 wire_frame;

		/*
		 * Try to figure out if we're an even or odd frame. If we set
		 * even and the current frame number is even the the transfer
		 * will happen immediately.  Similar if both are odd. If one is
		 * even and the other is odd then the transfer will happen when
		 * the frame number ticks.
		 *
		 * There's a bit of a balancing act to get this right.
		 * Sometimes we may want to send data in the current frame (AK
		 * right away).  We might want to do this if the frame number
		 * _just_ ticked, but we might also want to do this in order
		 * to continue a split transaction that happened late in a
		 * microframe (so we didn't know to queue the next transfer
		 * until the frame number had ticked).  The problem is that we
		 * need a lot of knowledge to know if there's actually still
		 * time to send things or if it would be better to wait until
		 * the next frame.
		 *
		 * We can look at how much time is left in the current frame
		 * and make a guess about whether we'll have time to transfer.
		 * We'll do that.
		 */

		/* Get speed host is running at */
		host_speed = (chan->speed != USB_SPEED_HIGH &&
			      !chan->do_split) ? chan->speed : USB_SPEED_HIGH;

		/* See how many bytes are in the periodic FIFO right now */
		fifo_space = (dwc2_readl(hsotg, HPTXSTS) &
			      TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT;
		bytes_in_fifo = sizeof(u32) *
				(hsotg->params.host_perio_tx_fifo_size -
				 fifo_space);

		/*
		 * Roughly estimate bus time for everything in the periodic
		 * queue + our new transfer.  This is "rough" because we're
		 * using a function that makes takes into account IN/OUT
		 * and INT/ISO and we're just slamming in one value for all
		 * transfers.  This should be an over-estimate and that should
		 * be OK, but we can probably tighten it.
		 */
		xfer_ns = usb_calc_bus_time(host_speed, false, false,
					    chan->xfer_len + bytes_in_fifo);
		xfer_us = NS_TO_US(xfer_ns);

		/* See what frame number we'll be at by the time we finish */
		frame_number = dwc2_hcd_get_future_frame_number(hsotg, xfer_us);

		/* This is when we were scheduled to be on the wire */
		wire_frame = dwc2_frame_num_inc(chan->qh->next_active_frame, 1);

		/*
		 * If we'd finish _after_ the frame we're scheduled in then
		 * it's hopeless.  Just schedule right away and hope for the
		 * best.  Note that it _might_ be wise to call back into the
		 * scheduler to pick a better frame, but this is better than
		 * nothing.
		 */
		if (dwc2_frame_num_gt(frame_number, wire_frame)) {
			dwc2_sch_vdbg(hsotg,
				      "QH=%p EO MISS fr=%04x=>%04x (%+d)\n",
				      chan->qh, wire_frame, frame_number,
				      dwc2_frame_num_dec(frame_number,
							 wire_frame));
			wire_frame = frame_number;

			/*
			 * We picked a different frame number; communicate this
			 * back to the scheduler so it doesn't try to schedule
			 * another in the same frame.
			 *
			 * Remember that next_active_frame is 1 before the wire
			 * frame.
			 */
			chan->qh->next_active_frame =
				dwc2_frame_num_dec(frame_number, 1);
		}

		if (wire_frame & 1)
			*hcchar |= HCCHAR_ODDFRM;
		else
			*hcchar &= ~HCCHAR_ODDFRM;
	}
}