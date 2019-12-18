#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_request {int length; scalar_t__ actual; int /*<<< orphan*/  status; int /*<<< orphan*/  no_interrupt; int /*<<< orphan*/  short_not_ok; int /*<<< orphan*/  zero; scalar_t__ dma; scalar_t__ buf; int /*<<< orphan*/  complete; } ;
struct usb_ep {int maxpacket; int /*<<< orphan*/  desc; } ;
struct ast_vhub_req {int active; int last_desc; int /*<<< orphan*/  queue; scalar_t__ act_count; int /*<<< orphan*/  internal; } ;
struct TYPE_6__ {scalar_t__ desc_mode; scalar_t__ is_in; int /*<<< orphan*/  enabled; } ;
struct ast_vhub_ep {TYPE_3__ epn; int /*<<< orphan*/  queue; TYPE_1__* dev; int /*<<< orphan*/  d_idx; struct ast_vhub* vhub; } ;
struct ast_vhub {int /*<<< orphan*/  lock; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  gadget; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*) ; 
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*,...) ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  ast_vhub_epn_kick (struct ast_vhub_ep*,struct ast_vhub_req*) ; 
 int /*<<< orphan*/  ast_vhub_epn_kick_desc (struct ast_vhub_ep*,struct ast_vhub_req*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_ep* to_ast_ep (struct usb_ep*) ; 
 struct ast_vhub_req* to_ast_req (struct usb_request*) ; 
 int usb_gadget_map_request (int /*<<< orphan*/ *,struct usb_request*,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_epn_queue(struct usb_ep* u_ep, struct usb_request *u_req,
			      gfp_t gfp_flags)
{
	struct ast_vhub_req *req = to_ast_req(u_req);
	struct ast_vhub_ep *ep = to_ast_ep(u_ep);
	struct ast_vhub *vhub = ep->vhub;
	unsigned long flags;
	bool empty;
	int rc;

	/* Paranoid checks */
	if (!u_req || !u_req->complete || !u_req->buf) {
		dev_warn(&vhub->pdev->dev, "Bogus EPn request ! u_req=%p\n", u_req);
		if (u_req) {
			dev_warn(&vhub->pdev->dev, "complete=%p internal=%d\n",
				 u_req->complete, req->internal);
		}
		return -EINVAL;
	}

	/* Endpoint enabled ? */
	if (!ep->epn.enabled || !u_ep->desc || !ep->dev || !ep->d_idx ||
	    !ep->dev->enabled) {
		EPDBG(ep, "Enqueuing request on wrong or disabled EP\n");
		return -ESHUTDOWN;
	}

	/* Map request for DMA if possible. For now, the rule for DMA is
	 * that:
	 *
	 *  * For single stage mode (no descriptors):
	 *
	 *   - The buffer is aligned to a 8 bytes boundary (HW requirement)
	 *   - For a OUT endpoint, the request size is a multiple of the EP
	 *     packet size (otherwise the controller will DMA past the end
	 *     of the buffer if the host is sending a too long packet).
	 *
	 *  * For descriptor mode (tx only for now), always.
	 *
	 * We could relax the latter by making the decision to use the bounce
	 * buffer based on the size of a given *segment* of the request rather
	 * than the whole request.
	 */
	if (ep->epn.desc_mode ||
	    ((((unsigned long)u_req->buf & 7) == 0) &&
	     (ep->epn.is_in || !(u_req->length & (u_ep->maxpacket - 1))))) {
		rc = usb_gadget_map_request(&ep->dev->gadget, u_req,
					    ep->epn.is_in);
		if (rc) {
			dev_warn(&vhub->pdev->dev,
				 "Request mapping failure %d\n", rc);
			return rc;
		}
	} else
		u_req->dma = 0;

	EPVDBG(ep, "enqueue req @%p\n", req);
	EPVDBG(ep, " l=%d dma=0x%x zero=%d noshort=%d noirq=%d is_in=%d\n",
	       u_req->length, (u32)u_req->dma, u_req->zero,
	       u_req->short_not_ok, u_req->no_interrupt,
	       ep->epn.is_in);

	/* Initialize request progress fields */
	u_req->status = -EINPROGRESS;
	u_req->actual = 0;
	req->act_count = 0;
	req->active = false;
	req->last_desc = -1;
	spin_lock_irqsave(&vhub->lock, flags);
	empty = list_empty(&ep->queue);

	/* Add request to list and kick processing if empty */
	list_add_tail(&req->queue, &ep->queue);
	if (empty) {
		if (ep->epn.desc_mode)
			ast_vhub_epn_kick_desc(ep, req);
		else
			ast_vhub_epn_kick(ep, req);
	}
	spin_unlock_irqrestore(&vhub->lock, flags);

	return 0;
}