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
struct TYPE_2__ {int status; } ;
struct dwc3_request {int needs_extra_trb; int /*<<< orphan*/ * trb; int /*<<< orphan*/  direction; TYPE_1__ request; scalar_t__ remaining; int /*<<< orphan*/  list; } ;
struct dwc3_ep {int number; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  sysdev; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dwc3_gadget_giveback (struct dwc3_request*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request_by_dev (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_gadget_del_and_unmap_request(struct dwc3_ep *dep,
		struct dwc3_request *req, int status)
{
	struct dwc3			*dwc = dep->dwc;

	list_del(&req->list);
	req->remaining = 0;
	req->needs_extra_trb = false;

	if (req->request.status == -EINPROGRESS)
		req->request.status = status;

	if (req->trb)
		usb_gadget_unmap_request_by_dev(dwc->sysdev,
				&req->request, req->direction);

	req->trb = NULL;
	trace_dwc3_gadget_giveback(req);

	if (dep->number > 1)
		pm_runtime_put(dwc->dev);
}