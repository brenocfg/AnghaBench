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
struct dwc3_event_depevt {int status; int endpoint_number; } ;
struct dwc3_ep {int /*<<< orphan*/  pending_list; } ;
struct dwc3 {int ep0_expect_in; int delayed_status; int /*<<< orphan*/  gadget; struct dwc3_ep** eps; int /*<<< orphan*/  ep0state; int /*<<< orphan*/  ep0_next_event; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DEPEVT_STATUS_CONTROL_DATA 129 
#define  DEPEVT_STATUS_CONTROL_STATUS 128 
 int /*<<< orphan*/  DWC3_EP0_NRDY_STATUS ; 
 int /*<<< orphan*/  EP0_STATUS_PHASE ; 
 int /*<<< orphan*/  USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_ep0_do_control_status (struct dwc3*,struct dwc3_event_depevt const*) ; 
 int /*<<< orphan*/  dwc3_ep0_end_control_data (struct dwc3*,struct dwc3_ep*) ; 
 int /*<<< orphan*/  dwc3_ep0_stall_and_restart (struct dwc3*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_ep0_xfernotready(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	switch (event->status) {
	case DEPEVT_STATUS_CONTROL_DATA:
		/*
		 * We already have a DATA transfer in the controller's cache,
		 * if we receive a XferNotReady(DATA) we will ignore it, unless
		 * it's for the wrong direction.
		 *
		 * In that case, we must issue END_TRANSFER command to the Data
		 * Phase we already have started and issue SetStall on the
		 * control endpoint.
		 */
		if (dwc->ep0_expect_in != event->endpoint_number) {
			struct dwc3_ep	*dep = dwc->eps[dwc->ep0_expect_in];

			dev_err(dwc->dev, "unexpected direction for Data Phase\n");
			dwc3_ep0_end_control_data(dwc, dep);
			dwc3_ep0_stall_and_restart(dwc);
			return;
		}

		break;

	case DEPEVT_STATUS_CONTROL_STATUS:
		if (dwc->ep0_next_event != DWC3_EP0_NRDY_STATUS)
			return;

		dwc->ep0state = EP0_STATUS_PHASE;

		if (dwc->delayed_status) {
			struct dwc3_ep *dep = dwc->eps[0];

			WARN_ON_ONCE(event->endpoint_number != 1);
			/*
			 * We should handle the delay STATUS phase here if the
			 * request for handling delay STATUS has been queued
			 * into the list.
			 */
			if (!list_empty(&dep->pending_list)) {
				dwc->delayed_status = false;
				usb_gadget_set_state(&dwc->gadget,
						     USB_STATE_CONFIGURED);
				dwc3_ep0_do_control_status(dwc, event);
			}

			return;
		}

		dwc3_ep0_do_control_status(dwc, event);
	}
}