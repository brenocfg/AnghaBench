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
struct usbhsg_uep {int /*<<< orphan*/  ep; } ;
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/ * handler; } ;
struct usb_request {int length; scalar_t__ zero; int /*<<< orphan*/ * buf; int /*<<< orphan*/  complete; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __usbhsg_recip_send_complete ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct usb_request* usb_ep_alloc_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ *,struct usb_request*) ; 
 int /*<<< orphan*/  usbhs_fifo_pio_push_handler ; 
 struct usbhsg_uep* usbhsg_gpriv_to_dcp (struct usbhsg_gpriv*) ; 
 struct device* usbhsg_gpriv_to_dev (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_queue_push (struct usbhsg_uep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_req_to_ureq (struct usb_request*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 

__attribute__((used)) static void __usbhsg_recip_send_status(struct usbhsg_gpriv *gpriv,
				       unsigned short status)
{
	struct usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	struct device *dev = usbhsg_gpriv_to_dev(gpriv);
	struct usb_request *req;
	__le16 *buf;

	/* alloc new usb_request for recip */
	req = usb_ep_alloc_request(&dcp->ep, GFP_ATOMIC);
	if (!req) {
		dev_err(dev, "recip request allocation fail\n");
		return;
	}

	/* alloc recip data buffer */
	buf = kmalloc(sizeof(*buf), GFP_ATOMIC);
	if (!buf) {
		usb_ep_free_request(&dcp->ep, req);
		return;
	}

	/* recip data is status */
	*buf = cpu_to_le16(status);

	/* allocated usb_request/buffer will be freed */
	req->complete	= __usbhsg_recip_send_complete;
	req->buf	= buf;
	req->length	= sizeof(*buf);
	req->zero	= 0;

	/* push packet */
	pipe->handler = &usbhs_fifo_pio_push_handler;
	usbhsg_queue_push(dcp, usbhsg_req_to_ureq(req));
}