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
struct nbu2ss_udc {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int status; scalar_t__ dma; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
struct nbu2ss_req {TYPE_1__ req; int /*<<< orphan*/  queue; } ;
struct nbu2ss_ep {scalar_t__ direct; scalar_t__ epnum; int /*<<< orphan*/  ep; int /*<<< orphan*/  queue; scalar_t__ stalled; struct nbu2ss_udc* udc; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EINPROGRESS ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  _nbu2ss_dma_unmap_single (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*,scalar_t__) ; 
 int /*<<< orphan*/  _nbu2ss_epn_set_stall (struct nbu2ss_udc*,struct nbu2ss_ep*) ; 
 int /*<<< orphan*/  _nbu2ss_fifo_flush (struct nbu2ss_udc*,struct nbu2ss_ep*) ; 
 int /*<<< orphan*/  _nbu2ss_restert_transfer (struct nbu2ss_ep*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void _nbu2ss_ep_done(struct nbu2ss_ep *ep,
			    struct nbu2ss_req *req,
			    int status)
{
	struct nbu2ss_udc *udc = ep->udc;

	list_del_init(&req->queue);

	if (status == -ECONNRESET)
		_nbu2ss_fifo_flush(udc, ep);

	if (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;

	if (ep->stalled) {
		_nbu2ss_epn_set_stall(udc, ep);
	} else {
		if (!list_empty(&ep->queue))
			_nbu2ss_restert_transfer(ep);
	}

#ifdef USE_DMA
	if ((ep->direct == USB_DIR_OUT) && (ep->epnum > 0) &&
	    (req->req.dma != 0))
		_nbu2ss_dma_unmap_single(udc, ep, req, USB_DIR_OUT);
#endif

	spin_unlock(&udc->lock);
	req->req.complete(&ep->ep, &req->req);
	spin_lock(&udc->lock);
}