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
struct usb_request {int dummy; } ;
struct bcm63xx_udc {int ep0state; struct usb_request* ep0_reply; int /*<<< orphan*/ * ep0_request; int /*<<< orphan*/ * iudma; int /*<<< orphan*/  ep0_req_completed; scalar_t__ ep0_req_shutdown; scalar_t__ ep0_req_reset; } ;
typedef  enum bcm63xx_ep0_state { ____Placeholder_bcm63xx_ep0_state } bcm63xx_ep0_state ;

/* Variables and functions */
 int /*<<< orphan*/  BCM63XX_MAX_CTRL_PKT ; 
 int EAGAIN ; 
#define  EP0_IDLE 136 
#define  EP0_IN_DATA_PHASE_COMPLETE 135 
#define  EP0_IN_DATA_PHASE_SETUP 134 
#define  EP0_IN_FAKE_STATUS_PHASE 133 
#define  EP0_OUT_DATA_PHASE_COMPLETE 132 
#define  EP0_OUT_DATA_PHASE_SETUP 131 
#define  EP0_OUT_STATUS_PHASE 130 
#define  EP0_REQUEUE 129 
#define  EP0_SHUTDOWN 128 
 size_t IUDMA_EP0_RXCHAN ; 
 size_t IUDMA_EP0_TXCHAN ; 
 int /*<<< orphan*/  bcm63xx_ep0_complete (struct bcm63xx_udc*,struct usb_request*,int /*<<< orphan*/ ) ; 
 int bcm63xx_ep0_do_idle (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_ep0_internal_request (struct bcm63xx_udc*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm63xx_ep0_map_write (struct bcm63xx_udc*,size_t,struct usb_request*) ; 
 int /*<<< orphan*/  bcm63xx_ep0_nuke_reply (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  bcm63xx_ep0_read_complete (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  iudma_reset_channel (struct bcm63xx_udc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm63xx_ep0_one_round(struct bcm63xx_udc *udc)
{
	enum bcm63xx_ep0_state ep0state = udc->ep0state;
	bool shutdown = udc->ep0_req_reset || udc->ep0_req_shutdown;

	switch (udc->ep0state) {
	case EP0_REQUEUE:
		/* set up descriptor to receive SETUP packet */
		bcm63xx_ep0_internal_request(udc, IUDMA_EP0_RXCHAN,
					     BCM63XX_MAX_CTRL_PKT);
		ep0state = EP0_IDLE;
		break;
	case EP0_IDLE:
		return bcm63xx_ep0_do_idle(udc);
	case EP0_IN_DATA_PHASE_SETUP:
		/*
		 * Normal case: TX request is in ep0_reply (queued by the
		 * callback), or will be queued shortly.  When it's here,
		 * send it to the HW and go to EP0_IN_DATA_PHASE_COMPLETE.
		 *
		 * Shutdown case: Stop waiting for the reply.  Just
		 * REQUEUE->IDLE.  The gadget driver is NOT expected to
		 * queue anything else now.
		 */
		if (udc->ep0_reply) {
			bcm63xx_ep0_map_write(udc, IUDMA_EP0_TXCHAN,
					      udc->ep0_reply);
			ep0state = EP0_IN_DATA_PHASE_COMPLETE;
		} else if (shutdown) {
			ep0state = EP0_REQUEUE;
		}
		break;
	case EP0_IN_DATA_PHASE_COMPLETE: {
		/*
		 * Normal case: TX packet (ep0_reply) is in flight; wait for
		 * it to finish, then go back to REQUEUE->IDLE.
		 *
		 * Shutdown case: Reset the TX channel, send -ESHUTDOWN
		 * completion to the gadget driver, then REQUEUE->IDLE.
		 */
		if (udc->ep0_req_completed) {
			udc->ep0_reply = NULL;
			bcm63xx_ep0_read_complete(udc);
			/*
			 * the "ack" sometimes gets eaten (see
			 * bcm63xx_ep0_do_idle)
			 */
			ep0state = EP0_REQUEUE;
		} else if (shutdown) {
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			bcm63xx_ep0_nuke_reply(udc, 1);
			ep0state = EP0_REQUEUE;
		}
		break;
	}
	case EP0_OUT_DATA_PHASE_SETUP:
		/* Similar behavior to EP0_IN_DATA_PHASE_SETUP */
		if (udc->ep0_reply) {
			bcm63xx_ep0_map_write(udc, IUDMA_EP0_RXCHAN,
					      udc->ep0_reply);
			ep0state = EP0_OUT_DATA_PHASE_COMPLETE;
		} else if (shutdown) {
			ep0state = EP0_REQUEUE;
		}
		break;
	case EP0_OUT_DATA_PHASE_COMPLETE: {
		/* Similar behavior to EP0_IN_DATA_PHASE_COMPLETE */
		if (udc->ep0_req_completed) {
			udc->ep0_reply = NULL;
			bcm63xx_ep0_read_complete(udc);

			/* send 0-byte ack to host */
			bcm63xx_ep0_internal_request(udc, IUDMA_EP0_TXCHAN, 0);
			ep0state = EP0_OUT_STATUS_PHASE;
		} else if (shutdown) {
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_RXCHAN]);
			bcm63xx_ep0_nuke_reply(udc, 0);
			ep0state = EP0_REQUEUE;
		}
		break;
	}
	case EP0_OUT_STATUS_PHASE:
		/*
		 * Normal case: 0-byte OUT ack packet is in flight; wait
		 * for it to finish, then go back to REQUEUE->IDLE.
		 *
		 * Shutdown case: just cancel the transmission.  Don't bother
		 * calling the completion, because it originated from this
		 * function anyway.  Then go back to REQUEUE->IDLE.
		 */
		if (udc->ep0_req_completed) {
			bcm63xx_ep0_read_complete(udc);
			ep0state = EP0_REQUEUE;
		} else if (shutdown) {
			iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			udc->ep0_request = NULL;
			ep0state = EP0_REQUEUE;
		}
		break;
	case EP0_IN_FAKE_STATUS_PHASE: {
		/*
		 * Normal case: we spoofed a SETUP packet and are now
		 * waiting for the gadget driver to send a 0-byte reply.
		 * This doesn't actually get sent to the HW because the
		 * HW has already sent its own reply.  Once we get the
		 * response, return to IDLE.
		 *
		 * Shutdown case: return to IDLE immediately.
		 *
		 * Note that the ep0 RX descriptor has remained queued
		 * (and possibly unfilled) during this entire transaction.
		 * The HW datapath (IUDMA) never even sees SET_CONFIGURATION
		 * or SET_INTERFACE transactions.
		 */
		struct usb_request *r = udc->ep0_reply;

		if (!r) {
			if (shutdown)
				ep0state = EP0_IDLE;
			break;
		}

		bcm63xx_ep0_complete(udc, r, 0);
		udc->ep0_reply = NULL;
		ep0state = EP0_IDLE;
		break;
	}
	case EP0_SHUTDOWN:
		break;
	}

	if (udc->ep0state == ep0state)
		return -EAGAIN;

	udc->ep0state = ep0state;
	return 0;
}