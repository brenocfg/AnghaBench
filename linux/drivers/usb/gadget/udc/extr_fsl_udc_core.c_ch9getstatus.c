#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_5__ {int is_selfpowered; } ;
struct fsl_udc {int remote_wakeup; int /*<<< orphan*/  ep0_state; struct fsl_req* status_req; int /*<<< orphan*/  ep0_dir; TYPE_1__ gadget; struct fsl_ep* eps; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  complete; scalar_t__ actual; int /*<<< orphan*/  status; scalar_t__ buf; } ;
struct fsl_req {int /*<<< orphan*/  queue; TYPE_4__ req; scalar_t__ dtd_count; struct fsl_ep* ep; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc; } ;
struct fsl_ep {int /*<<< orphan*/  queue; TYPE_3__* udc; TYPE_2__ ep; } ;
struct TYPE_7__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_STATE_XMIT ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EP_DIR_OUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int USB_ENDPOINT_HALT ; 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_RECIP_MASK ; 
 int cpu_to_le16 (int) ; 
 int dr_ep_get_stall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ep0_prime_status (struct fsl_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0stall (struct fsl_udc*) ; 
 int /*<<< orphan*/  ep_index (struct fsl_ep*) ; 
 int /*<<< orphan*/  ep_is_in (struct fsl_ep*) ; 
 int /*<<< orphan*/  fsl_noop_complete ; 
 int /*<<< orphan*/  fsl_queue_td (struct fsl_ep*,struct fsl_req*) ; 
 scalar_t__ fsl_req_to_dtd (struct fsl_req*,int /*<<< orphan*/ ) ; 
 struct fsl_ep* get_ep_by_pipe (struct fsl_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pipe_by_windex (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usb_gadget_map_request (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ch9getstatus(struct fsl_udc *udc, u8 request_type, u16 value,
		u16 index, u16 length)
{
	u16 tmp = 0;		/* Status, cpu endian */
	struct fsl_req *req;
	struct fsl_ep *ep;
	int ret;

	ep = &udc->eps[0];

	if ((request_type & USB_RECIP_MASK) == USB_RECIP_DEVICE) {
		/* Get device status */
		tmp = udc->gadget.is_selfpowered;
		tmp |= udc->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP;
	} else if ((request_type & USB_RECIP_MASK) == USB_RECIP_INTERFACE) {
		/* Get interface status */
		/* We don't have interface information in udc driver */
		tmp = 0;
	} else if ((request_type & USB_RECIP_MASK) == USB_RECIP_ENDPOINT) {
		/* Get endpoint status */
		struct fsl_ep *target_ep;

		target_ep = get_ep_by_pipe(udc, get_pipe_by_windex(index));

		/* stall if endpoint doesn't exist */
		if (!target_ep->ep.desc)
			goto stall;
		tmp = dr_ep_get_stall(ep_index(target_ep), ep_is_in(target_ep))
				<< USB_ENDPOINT_HALT;
	}

	udc->ep0_dir = USB_DIR_IN;
	/* Borrow the per device status_req */
	req = udc->status_req;
	/* Fill in the reqest structure */
	*((u16 *) req->req.buf) = cpu_to_le16(tmp);

	req->ep = ep;
	req->req.length = 2;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->req.complete = fsl_noop_complete;
	req->dtd_count = 0;

	ret = usb_gadget_map_request(&ep->udc->gadget, &req->req, ep_is_in(ep));
	if (ret)
		goto stall;

	/* prime the data phase */
	if ((fsl_req_to_dtd(req, GFP_ATOMIC) == 0))
		fsl_queue_td(ep, req);
	else			/* no mem */
		goto stall;

	list_add_tail(&req->queue, &ep->queue);
	udc->ep0_state = DATA_STATE_XMIT;
	if (ep0_prime_status(udc, EP_DIR_OUT))
		ep0stall(udc);

	return;
stall:
	ep0stall(udc);
}