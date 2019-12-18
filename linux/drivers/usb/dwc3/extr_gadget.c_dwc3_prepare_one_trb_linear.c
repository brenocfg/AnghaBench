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
struct dwc3_trb {int dummy; } ;
struct TYPE_4__ {unsigned int length; int /*<<< orphan*/  no_interrupt; int /*<<< orphan*/  short_not_ok; int /*<<< orphan*/  stream_id; scalar_t__ zero; } ;
struct dwc3_request {int needs_extra_trb; TYPE_2__ request; int /*<<< orphan*/  num_trbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {size_t trb_enqueue; struct dwc3_trb* trb_pool; struct dwc3* dwc; TYPE_1__ endpoint; } ;
struct dwc3 {int /*<<< orphan*/  bounce_addr; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __dwc3_prepare_one_trb (struct dwc3_ep*,struct dwc3_trb*,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_prepare_one_trb (struct dwc3_ep*,struct dwc3_request*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_out (int /*<<< orphan*/ ) ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_prepare_one_trb_linear(struct dwc3_ep *dep,
		struct dwc3_request *req)
{
	unsigned int length = req->request.length;
	unsigned int maxp = usb_endpoint_maxp(dep->endpoint.desc);
	unsigned int rem = length % maxp;

	if ((!length || rem) && usb_endpoint_dir_out(dep->endpoint.desc)) {
		struct dwc3	*dwc = dep->dwc;
		struct dwc3_trb	*trb;

		req->needs_extra_trb = true;

		/* prepare normal TRB */
		dwc3_prepare_one_trb(dep, req, true, 0);

		/* Now prepare one extra TRB to align transfer size */
		trb = &dep->trb_pool[dep->trb_enqueue];
		req->num_trbs++;
		__dwc3_prepare_one_trb(dep, trb, dwc->bounce_addr, maxp - rem,
				false, 1, req->request.stream_id,
				req->request.short_not_ok,
				req->request.no_interrupt);
	} else if (req->request.zero && req->request.length &&
		   (IS_ALIGNED(req->request.length, maxp))) {
		struct dwc3	*dwc = dep->dwc;
		struct dwc3_trb	*trb;

		req->needs_extra_trb = true;

		/* prepare normal TRB */
		dwc3_prepare_one_trb(dep, req, true, 0);

		/* Now prepare one extra TRB to handle ZLP */
		trb = &dep->trb_pool[dep->trb_enqueue];
		req->num_trbs++;
		__dwc3_prepare_one_trb(dep, trb, dwc->bounce_addr, 0,
				false, 1, req->request.stream_id,
				req->request.short_not_ok,
				req->request.no_interrupt);
	} else {
		dwc3_prepare_one_trb(dep, req, false, 0);
	}
}