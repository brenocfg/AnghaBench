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
typedef  scalar_t__ u32 ;
struct dwc3_trb {int /*<<< orphan*/  size; } ;
struct dwc3_request {int dummy; } ;
struct dwc3_event_depevt {int dummy; } ;
struct dwc3_ep {int /*<<< orphan*/  pending_list; } ;
struct dwc3 {int setup_packet_pending; int /*<<< orphan*/  ep0state; int /*<<< orphan*/  test_mode_nr; int /*<<< orphan*/  dev; scalar_t__ test_mode; struct dwc3_trb* ep0_trb; struct dwc3_ep** eps; } ;

/* Variables and functions */
 scalar_t__ DWC3_TRBSTS_SETUP_PENDING ; 
 scalar_t__ DWC3_TRB_SIZE_TRBSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EP0_SETUP_PHASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_ep0_out_start (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_ep0_stall_and_restart (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_giveback (struct dwc3_ep*,struct dwc3_request*,int /*<<< orphan*/ ) ; 
 int dwc3_gadget_set_test_mode (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct dwc3_request* next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dwc3_complete_trb (struct dwc3_ep*,struct dwc3_trb*) ; 

__attribute__((used)) static void dwc3_ep0_complete_status(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct dwc3_request	*r;
	struct dwc3_ep		*dep;
	struct dwc3_trb		*trb;
	u32			status;

	dep = dwc->eps[0];
	trb = dwc->ep0_trb;

	trace_dwc3_complete_trb(dep, trb);

	if (!list_empty(&dep->pending_list)) {
		r = next_request(&dep->pending_list);

		dwc3_gadget_giveback(dep, r, 0);
	}

	if (dwc->test_mode) {
		int ret;

		ret = dwc3_gadget_set_test_mode(dwc, dwc->test_mode_nr);
		if (ret < 0) {
			dev_err(dwc->dev, "invalid test #%d\n",
					dwc->test_mode_nr);
			dwc3_ep0_stall_and_restart(dwc);
			return;
		}
	}

	status = DWC3_TRB_SIZE_TRBSTS(trb->size);
	if (status == DWC3_TRBSTS_SETUP_PENDING)
		dwc->setup_packet_pending = true;

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
}