#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_request {struct usb_request* context; int /*<<< orphan*/  buf; void* complete; } ;
struct usb_composite_dev {int dummy; } ;
struct f_loopback {int qlen; int /*<<< orphan*/  in_ep; TYPE_1__* out_ep; int /*<<< orphan*/  buflen; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  free_ep_req (TYPE_1__*,struct usb_request*) ; 
 struct usb_request* lb_alloc_ep_req (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* loopback_complete ; 
 struct usb_request* usb_ep_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,struct usb_request*) ; 
 int usb_ep_queue (TYPE_1__*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_requests(struct usb_composite_dev *cdev,
			  struct f_loopback *loop)
{
	struct usb_request *in_req, *out_req;
	int i;
	int result = 0;

	/*
	 * allocate a bunch of read buffers and queue them all at once.
	 * we buffer at most 'qlen' transfers; We allocate buffers only
	 * for out transfer and reuse them in IN transfers to implement
	 * our loopback functionality
	 */
	for (i = 0; i < loop->qlen && result == 0; i++) {
		result = -ENOMEM;

		in_req = usb_ep_alloc_request(loop->in_ep, GFP_ATOMIC);
		if (!in_req)
			goto fail;

		out_req = lb_alloc_ep_req(loop->out_ep, loop->buflen);
		if (!out_req)
			goto fail_in;

		in_req->complete = loopback_complete;
		out_req->complete = loopback_complete;

		in_req->buf = out_req->buf;
		/* length will be set in complete routine */
		in_req->context = out_req;
		out_req->context = in_req;

		result = usb_ep_queue(loop->out_ep, out_req, GFP_ATOMIC);
		if (result) {
			ERROR(cdev, "%s queue req --> %d\n",
					loop->out_ep->name, result);
			goto fail_out;
		}
	}

	return 0;

fail_out:
	free_ep_req(loop->out_ep, out_req);
fail_in:
	usb_ep_free_request(loop->in_ep, in_req);
fail:
	return result;
}