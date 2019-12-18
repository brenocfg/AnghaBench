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
struct dwc3_request {int /*<<< orphan*/  request; int /*<<< orphan*/  status; } ;
struct dwc3_ep {int /*<<< orphan*/  endpoint; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_REQUEST_STATUS_COMPLETED ; 
 int /*<<< orphan*/  dwc3_gadget_del_and_unmap_request (struct dwc3_ep*,struct dwc3_request*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dwc3_gadget_giveback(struct dwc3_ep *dep, struct dwc3_request *req,
		int status)
{
	struct dwc3			*dwc = dep->dwc;

	dwc3_gadget_del_and_unmap_request(dep, req, status);
	req->status = DWC3_REQUEST_STATUS_COMPLETED;

	spin_unlock(&dwc->lock);
	usb_gadget_giveback_request(&dep->endpoint, &req->request);
	spin_lock(&dwc->lock);
}