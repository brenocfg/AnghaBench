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
struct vudc {int /*<<< orphan*/  lock; } ;
struct vrequest {int /*<<< orphan*/  req_entry; } ;
struct vep {int /*<<< orphan*/  req_queue; } ;
struct usb_request {int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct usb_ep {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 struct vudc* ep_to_vudc (struct vep*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vep* to_vep (struct usb_ep*) ; 
 struct vrequest* to_vrequest (struct usb_request*) ; 

__attribute__((used)) static int vep_queue(struct usb_ep *_ep, struct usb_request *_req,
		gfp_t mem_flags)
{
	struct vep *ep;
	struct vrequest *req;
	struct vudc *udc;
	unsigned long flags;

	if (!_ep || !_req)
		return -EINVAL;

	ep = to_vep(_ep);
	req = to_vrequest(_req);
	udc = ep_to_vudc(ep);

	spin_lock_irqsave(&udc->lock, flags);
	_req->actual = 0;
	_req->status = -EINPROGRESS;

	list_add_tail(&req->req_entry, &ep->req_queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}