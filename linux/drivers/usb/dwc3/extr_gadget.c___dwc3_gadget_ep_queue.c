#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct dwc3_request {scalar_t__ status; int /*<<< orphan*/  list; TYPE_2__ request; struct dwc3_ep* dep; } ;
struct TYPE_5__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {int flags; TYPE_1__ endpoint; int /*<<< orphan*/  pending_list; TYPE_2__* name; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DWC3_EP_PENDING_REQUEST ; 
 int DWC3_EP_TRANSFER_STARTED ; 
 scalar_t__ DWC3_REQUEST_STATUS_COMPLETED ; 
 scalar_t__ DWC3_REQUEST_STATUS_QUEUED ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int ESHUTDOWN ; 
 scalar_t__ WARN (int,char*,TYPE_2__*,TYPE_2__*) ; 
 int __dwc3_gadget_kick_transfer (struct dwc3_ep*) ; 
 int __dwc3_gadget_start_isoc (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dwc3_ep_queue (struct dwc3_request*) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dwc3_gadget_ep_queue(struct dwc3_ep *dep, struct dwc3_request *req)
{
	struct dwc3		*dwc = dep->dwc;

	if (!dep->endpoint.desc) {
		dev_err(dwc->dev, "%s: can't queue to disabled endpoint\n",
				dep->name);
		return -ESHUTDOWN;
	}

	if (WARN(req->dep != dep, "request %pK belongs to '%s'\n",
				&req->request, req->dep->name))
		return -EINVAL;

	if (WARN(req->status < DWC3_REQUEST_STATUS_COMPLETED,
				"%s: request %pK already in flight\n",
				dep->name, &req->request))
		return -EINVAL;

	pm_runtime_get(dwc->dev);

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;

	trace_dwc3_ep_queue(req);

	list_add_tail(&req->list, &dep->pending_list);
	req->status = DWC3_REQUEST_STATUS_QUEUED;

	/*
	 * NOTICE: Isochronous endpoints should NEVER be prestarted. We must
	 * wait for a XferNotReady event so we will know what's the current
	 * (micro-)frame number.
	 *
	 * Without this trick, we are very, very likely gonna get Bus Expiry
	 * errors which will force us issue EndTransfer command.
	 */
	if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
		if (!(dep->flags & DWC3_EP_PENDING_REQUEST) &&
				!(dep->flags & DWC3_EP_TRANSFER_STARTED))
			return 0;

		if ((dep->flags & DWC3_EP_PENDING_REQUEST)) {
			if (!(dep->flags & DWC3_EP_TRANSFER_STARTED)) {
				return __dwc3_gadget_start_isoc(dep);
			}
		}
	}

	return __dwc3_gadget_kick_transfer(dep);
}