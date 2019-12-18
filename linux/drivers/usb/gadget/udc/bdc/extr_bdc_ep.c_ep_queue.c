#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct bdc_req {TYPE_2__ usb_req; int /*<<< orphan*/  epnum; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc; } ;
struct bdc_ep {int /*<<< orphan*/  dir; int /*<<< orphan*/  ep_num; struct bdc* bdc; TYPE_1__ usb_ep; } ;
struct bdc {int /*<<< orphan*/  dev; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int bdc_queue_xfr (struct bdc*,struct bdc_req*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int usb_gadget_map_request (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep_queue(struct bdc_ep *ep, struct bdc_req *req)
{
	struct bdc *bdc;
	int ret = 0;

	if (!req || !ep->usb_ep.desc)
		return -EINVAL;

	bdc = ep->bdc;

	req->usb_req.actual = 0;
	req->usb_req.status = -EINPROGRESS;
	req->epnum = ep->ep_num;

	ret = usb_gadget_map_request(&bdc->gadget, &req->usb_req, ep->dir);
	if (ret) {
		dev_err(bdc->dev, "dma mapping failed\n");
		return ret;
	}

	return bdc_queue_xfr(bdc, req);
}