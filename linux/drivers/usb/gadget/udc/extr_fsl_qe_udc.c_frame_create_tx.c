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
struct TYPE_2__ {scalar_t__ length; } ;
struct qe_req {TYPE_1__ req; } ;
struct qe_frame {int dummy; } ;
struct qe_ep {scalar_t__ sent; struct qe_req* tx_req; } ;

/* Variables and functions */
 int ENODEV ; 
 int qe_usb_senddata (struct qe_ep*,struct qe_frame*) ; 
 int sendnulldata (struct qe_ep*,struct qe_frame*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frame_create_tx(struct qe_ep *ep, struct qe_frame *frame)
{
	struct qe_req *req = ep->tx_req;
	int reval;

	if (req == NULL)
		return -ENODEV;

	if ((req->req.length - ep->sent) > 0)
		reval = qe_usb_senddata(ep, frame);
	else
		reval = sendnulldata(ep, frame, 0);

	return reval;
}