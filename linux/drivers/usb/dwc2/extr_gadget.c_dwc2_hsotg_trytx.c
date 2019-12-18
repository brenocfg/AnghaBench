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
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct dwc2_hsotg_req {TYPE_1__ req; } ;
struct dwc2_hsotg_ep {scalar_t__ index; int /*<<< orphan*/  dir_in; struct dwc2_hsotg_req* req; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dwc2_hsotg_ctrl_epint (struct dwc2_hsotg*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dwc2_hsotg_write_fifo (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,struct dwc2_hsotg_req*) ; 

__attribute__((used)) static int dwc2_hsotg_trytx(struct dwc2_hsotg *hsotg,
			    struct dwc2_hsotg_ep *hs_ep)
{
	struct dwc2_hsotg_req *hs_req = hs_ep->req;

	if (!hs_ep->dir_in || !hs_req) {
		/**
		 * if request is not enqueued, we disable interrupts
		 * for endpoints, excepting ep0
		 */
		if (hs_ep->index != 0)
			dwc2_hsotg_ctrl_epint(hsotg, hs_ep->index,
					      hs_ep->dir_in, 0);
		return 0;
	}

	if (hs_req->req.actual < hs_req->req.length) {
		dev_dbg(hsotg->dev, "trying to write more for ep%d\n",
			hs_ep->index);
		return dwc2_hsotg_write_fifo(hsotg, hs_ep, hs_req);
	}

	return 0;
}