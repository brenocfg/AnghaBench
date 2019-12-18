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
struct dwc2_hsotg {int /*<<< orphan*/  ctrl_req; TYPE_1__** eps_out; int /*<<< orphan*/  gadget; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_hsotg_ep_free_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

int dwc2_hsotg_remove(struct dwc2_hsotg *hsotg)
{
	usb_del_gadget_udc(&hsotg->gadget);
	dwc2_hsotg_ep_free_request(&hsotg->eps_out[0]->ep, hsotg->ctrl_req);

	return 0;
}