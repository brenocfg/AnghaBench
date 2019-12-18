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
struct dwc3_trb {int /*<<< orphan*/  ctrl; } ;
struct dwc3_request {int num_trbs; struct dwc3_trb* trb; } ;
struct dwc3_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_TRB_CTRL_HWO ; 
 int /*<<< orphan*/  dwc3_ep_inc_deq (struct dwc3_ep*) ; 

__attribute__((used)) static void dwc3_gadget_ep_skip_trbs(struct dwc3_ep *dep, struct dwc3_request *req)
{
	int i;

	/*
	 * If request was already started, this means we had to
	 * stop the transfer. With that we also need to ignore
	 * all TRBs used by the request, however TRBs can only
	 * be modified after completion of END_TRANSFER
	 * command. So what we do here is that we wait for
	 * END_TRANSFER completion and only after that, we jump
	 * over TRBs by clearing HWO and incrementing dequeue
	 * pointer.
	 */
	for (i = 0; i < req->num_trbs; i++) {
		struct dwc3_trb *trb;

		trb = req->trb + i;
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;
		dwc3_ep_inc_deq(dep);
	}

	req->num_trbs = 0;
}