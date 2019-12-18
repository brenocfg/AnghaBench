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
struct dwc3_request {int dummy; } ;
struct dwc3_ep {int /*<<< orphan*/  cancelled_list; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  started_list; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  dwc3_gadget_giveback (struct dwc3_ep*,struct dwc3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_stop_active_transfer (struct dwc3_ep*,int,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct dwc3_request* next_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_remove_requests(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	struct dwc3_request		*req;

	dwc3_stop_active_transfer(dep, true, false);

	/* - giveback all requests to gadget driver */
	while (!list_empty(&dep->started_list)) {
		req = next_request(&dep->started_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	}

	while (!list_empty(&dep->pending_list)) {
		req = next_request(&dep->pending_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	}

	while (!list_empty(&dep->cancelled_list)) {
		req = next_request(&dep->cancelled_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	}
}