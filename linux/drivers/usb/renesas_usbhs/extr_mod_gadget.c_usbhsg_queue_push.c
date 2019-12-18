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
struct usbhsg_uep {int dummy; } ;
struct usb_request {int /*<<< orphan*/  length; int /*<<< orphan*/  zero; int /*<<< orphan*/  buf; int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct usbhsg_request {struct usb_request req; } ;
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_pkt {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pkt_push (struct usbhs_pipe*,struct usbhs_pkt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbhs_pkt_start (struct usbhs_pipe*) ; 
 struct device* usbhsg_gpriv_to_dev (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_queue_done ; 
 struct usbhsg_gpriv* usbhsg_uep_to_gpriv (struct usbhsg_uep*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 
 struct usbhs_pkt* usbhsg_ureq_to_pkt (struct usbhsg_request*) ; 

__attribute__((used)) static void usbhsg_queue_push(struct usbhsg_uep *uep,
			      struct usbhsg_request *ureq)
{
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	struct device *dev = usbhsg_gpriv_to_dev(gpriv);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	struct usbhs_pkt *pkt = usbhsg_ureq_to_pkt(ureq);
	struct usb_request *req = &ureq->req;

	req->actual = 0;
	req->status = -EINPROGRESS;
	usbhs_pkt_push(pipe, pkt, usbhsg_queue_done,
		       req->buf, req->length, req->zero, -1);
	usbhs_pkt_start(pipe);

	dev_dbg(dev, "pipe %d : queue push (%d)\n",
		usbhs_pipe_number(pipe),
		req->length);
}