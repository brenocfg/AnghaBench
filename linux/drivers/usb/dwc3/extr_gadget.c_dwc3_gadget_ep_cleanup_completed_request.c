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
struct TYPE_2__ {scalar_t__ length; scalar_t__ actual; } ;
struct dwc3_request {int needs_extra_trb; scalar_t__ num_pending_sgs; scalar_t__ remaining; TYPE_1__ request; } ;
struct dwc3_event_depevt {int dummy; } ;
struct dwc3_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dwc3_gadget_kick_transfer (struct dwc3_ep*) ; 
 int dwc3_gadget_ep_reclaim_trb_linear (struct dwc3_ep*,struct dwc3_request*,struct dwc3_event_depevt const*,int) ; 
 int dwc3_gadget_ep_reclaim_trb_sg (struct dwc3_ep*,struct dwc3_request*,struct dwc3_event_depevt const*,int) ; 
 int /*<<< orphan*/  dwc3_gadget_ep_request_completed (struct dwc3_request*) ; 
 int /*<<< orphan*/  dwc3_gadget_giveback (struct dwc3_ep*,struct dwc3_request*,int) ; 

__attribute__((used)) static int dwc3_gadget_ep_cleanup_completed_request(struct dwc3_ep *dep,
		const struct dwc3_event_depevt *event,
		struct dwc3_request *req, int status)
{
	int ret;

	if (req->num_pending_sgs)
		ret = dwc3_gadget_ep_reclaim_trb_sg(dep, req, event,
				status);
	else
		ret = dwc3_gadget_ep_reclaim_trb_linear(dep, req, event,
				status);

	if (req->needs_extra_trb) {
		ret = dwc3_gadget_ep_reclaim_trb_linear(dep, req, event,
				status);
		req->needs_extra_trb = false;
	}

	req->request.actual = req->request.length - req->remaining;

	if (!dwc3_gadget_ep_request_completed(req) &&
			req->num_pending_sgs) {
		__dwc3_gadget_kick_transfer(dep);
		goto out;
	}

	dwc3_gadget_giveback(dep, req, status);

out:
	return ret;
}