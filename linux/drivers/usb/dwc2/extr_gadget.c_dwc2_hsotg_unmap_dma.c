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
struct usb_request {int dummy; } ;
struct dwc2_hsotg_req {struct usb_request req; } ;
struct dwc2_hsotg_ep {int /*<<< orphan*/  dir_in; } ;
struct dwc2_hsotg {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hsotg_unmap_dma(struct dwc2_hsotg *hsotg,
				 struct dwc2_hsotg_ep *hs_ep,
				struct dwc2_hsotg_req *hs_req)
{
	struct usb_request *req = &hs_req->req;

	usb_gadget_unmap_request(&hsotg->gadget, req, hs_ep->dir_in);
}