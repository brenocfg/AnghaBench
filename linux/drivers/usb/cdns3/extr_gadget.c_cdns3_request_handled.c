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
struct cdns3_trb {int control; } ;
struct cdns3_request {size_t start_trb; int end_trb; struct cdns3_trb* trb; } ;
struct cdns3_endpoint {int ccs; int dequeue; scalar_t__ type; int enqueue; scalar_t__ free_trbs; int num_trbs; struct cdns3_trb* trb_pool; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int EP_CMD_DRDY ; 
 int TRBS_PER_SEGMENT ; 
 int TRB_CYCLE ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int cdns3_get_dma_pos (struct cdns3_device*,struct cdns3_endpoint*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_request_handled (struct cdns3_request*,int,int) ; 

__attribute__((used)) static bool cdns3_request_handled(struct cdns3_endpoint *priv_ep,
				  struct cdns3_request *priv_req)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	struct cdns3_trb *trb = priv_req->trb;
	int current_index = 0;
	int handled = 0;
	int doorbell;

	current_index = cdns3_get_dma_pos(priv_dev, priv_ep);
	doorbell = !!(readl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);

	trb = &priv_ep->trb_pool[priv_req->start_trb];

	if ((trb->control  & TRB_CYCLE) != priv_ep->ccs)
		goto finish;

	if (doorbell == 1 && current_index == priv_ep->dequeue)
		goto finish;

	/* The corner case for TRBS_PER_SEGMENT equal 2). */
	if (TRBS_PER_SEGMENT == 2 && priv_ep->type != USB_ENDPOINT_XFER_ISOC) {
		handled = 1;
		goto finish;
	}

	if (priv_ep->enqueue == priv_ep->dequeue &&
	    priv_ep->free_trbs == 0) {
		handled = 1;
	} else if (priv_ep->dequeue < current_index) {
		if ((current_index == (priv_ep->num_trbs - 1)) &&
		    !priv_ep->dequeue)
			goto finish;

		if (priv_req->end_trb >= priv_ep->dequeue &&
		    priv_req->end_trb < current_index)
			handled = 1;
	} else if (priv_ep->dequeue  > current_index) {
		if (priv_req->end_trb  < current_index ||
		    priv_req->end_trb >= priv_ep->dequeue)
			handled = 1;
	}

finish:
	trace_cdns3_request_handled(priv_req, current_index, handled);

	return handled;
}