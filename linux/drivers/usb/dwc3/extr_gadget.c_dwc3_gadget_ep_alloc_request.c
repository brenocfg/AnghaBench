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
struct usb_ep {int dummy; } ;
struct dwc3_request {struct usb_request request; int /*<<< orphan*/  status; struct dwc3_ep* dep; int /*<<< orphan*/  epnum; int /*<<< orphan*/  direction; } ;
struct dwc3_ep {int /*<<< orphan*/  number; int /*<<< orphan*/  direction; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_REQUEST_STATUS_UNKNOWN ; 
 struct dwc3_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct dwc3_ep* to_dwc3_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  trace_dwc3_alloc_request (struct dwc3_request*) ; 

__attribute__((used)) static struct usb_request *dwc3_gadget_ep_alloc_request(struct usb_ep *ep,
		gfp_t gfp_flags)
{
	struct dwc3_request		*req;
	struct dwc3_ep			*dep = to_dwc3_ep(ep);

	req = kzalloc(sizeof(*req), gfp_flags);
	if (!req)
		return NULL;

	req->direction	= dep->direction;
	req->epnum	= dep->number;
	req->dep	= dep;
	req->status	= DWC3_REQUEST_STATUS_UNKNOWN;

	trace_dwc3_alloc_request(req);

	return &req->request;
}