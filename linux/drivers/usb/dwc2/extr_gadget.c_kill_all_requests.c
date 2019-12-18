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
struct dwc2_hsotg_req {int dummy; } ;
struct dwc2_hsotg_ep {unsigned int fifo_size; int /*<<< orphan*/  fifo_index; int /*<<< orphan*/  queue; int /*<<< orphan*/ * req; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dedicated_fifos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTXFSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_complete_request (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,struct dwc2_hsotg_req*,int) ; 
 int /*<<< orphan*/  dwc2_hsotg_txfifo_flush (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 struct dwc2_hsotg_req* get_ep_head (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kill_all_requests(struct dwc2_hsotg *hsotg,
			      struct dwc2_hsotg_ep *ep,
			      int result)
{
	unsigned int size;

	ep->req = NULL;

	while (!list_empty(&ep->queue)) {
		struct dwc2_hsotg_req *req = get_ep_head(ep);

		dwc2_hsotg_complete_request(hsotg, ep, req, result);
	}

	if (!hsotg->dedicated_fifos)
		return;
	size = (dwc2_readl(hsotg, DTXFSTS(ep->fifo_index)) & 0xffff) * 4;
	if (size < ep->fifo_size)
		dwc2_hsotg_txfifo_flush(hsotg, ep->fifo_index);
}