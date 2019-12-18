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
struct TYPE_2__ {int /*<<< orphan*/ * complete; scalar_t__ actual; int /*<<< orphan*/  status; scalar_t__ length; } ;
struct bdc_req {TYPE_1__ usb_req; struct bdc_ep* ep; } ;
struct bdc_ep {int dummy; } ;
struct bdc {struct bdc_ep** bdc_ep_array; struct bdc_req status_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  bdc_queue_xfr (struct bdc*,struct bdc_req*) ; 

__attribute__((used)) static int ep0_queue_status_stage(struct bdc *bdc)
{
	struct bdc_req *status_req;
	struct bdc_ep *ep;

	status_req = &bdc->status_req;
	ep = bdc->bdc_ep_array[1];
	status_req->ep = ep;
	status_req->usb_req.length = 0;
	status_req->usb_req.status = -EINPROGRESS;
	status_req->usb_req.actual = 0;
	status_req->usb_req.complete = NULL;
	bdc_queue_xfr(bdc, status_req);

	return 0;
}