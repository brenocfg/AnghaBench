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
typedef  int u32 ;
struct usb_ctrlrequest {int bRequestType; int bRequest; scalar_t__ wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct dwc2_hsotg_ep {int dir_in; } ;
struct dwc2_hsotg {int connected; int delayed_status; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; int /*<<< orphan*/  ep0_state; struct dwc2_hsotg_ep** eps_out; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCFG ; 
 int DCFG_DEVADDR_MASK ; 
 int DCFG_DEVADDR_SHIFT ; 
 int /*<<< orphan*/  DWC2_EP0_DATA_IN ; 
 int /*<<< orphan*/  DWC2_EP0_DATA_OUT ; 
 int /*<<< orphan*/  DWC2_EP0_STATUS_IN ; 
 int USB_DIR_IN ; 
 int USB_GADGET_DELAYED_STATUS ; 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
#define  USB_REQ_SET_FEATURE 128 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dwc2_hsotg_process_req_feature (struct dwc2_hsotg*,struct usb_ctrlrequest*) ; 
 int dwc2_hsotg_process_req_status (struct dwc2_hsotg*,struct usb_ctrlrequest*) ; 
 int dwc2_hsotg_send_reply (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_stall_ep0 (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static void dwc2_hsotg_process_control(struct dwc2_hsotg *hsotg,
				       struct usb_ctrlrequest *ctrl)
{
	struct dwc2_hsotg_ep *ep0 = hsotg->eps_out[0];
	int ret = 0;
	u32 dcfg;

	dev_dbg(hsotg->dev,
		"ctrl Type=%02x, Req=%02x, V=%04x, I=%04x, L=%04x\n",
		ctrl->bRequestType, ctrl->bRequest, ctrl->wValue,
		ctrl->wIndex, ctrl->wLength);

	if (ctrl->wLength == 0) {
		ep0->dir_in = 1;
		hsotg->ep0_state = DWC2_EP0_STATUS_IN;
	} else if (ctrl->bRequestType & USB_DIR_IN) {
		ep0->dir_in = 1;
		hsotg->ep0_state = DWC2_EP0_DATA_IN;
	} else {
		ep0->dir_in = 0;
		hsotg->ep0_state = DWC2_EP0_DATA_OUT;
	}

	if ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		switch (ctrl->bRequest) {
		case USB_REQ_SET_ADDRESS:
			hsotg->connected = 1;
			dcfg = dwc2_readl(hsotg, DCFG);
			dcfg &= ~DCFG_DEVADDR_MASK;
			dcfg |= (le16_to_cpu(ctrl->wValue) <<
				 DCFG_DEVADDR_SHIFT) & DCFG_DEVADDR_MASK;
			dwc2_writel(hsotg, dcfg, DCFG);

			dev_info(hsotg->dev, "new address %d\n", ctrl->wValue);

			ret = dwc2_hsotg_send_reply(hsotg, ep0, NULL, 0);
			return;

		case USB_REQ_GET_STATUS:
			ret = dwc2_hsotg_process_req_status(hsotg, ctrl);
			break;

		case USB_REQ_CLEAR_FEATURE:
		case USB_REQ_SET_FEATURE:
			ret = dwc2_hsotg_process_req_feature(hsotg, ctrl);
			break;
		}
	}

	/* as a fallback, try delivering it to the driver to deal with */

	if (ret == 0 && hsotg->driver) {
		spin_unlock(&hsotg->lock);
		ret = hsotg->driver->setup(&hsotg->gadget, ctrl);
		spin_lock(&hsotg->lock);
		if (ret < 0)
			dev_dbg(hsotg->dev, "driver->setup() ret %d\n", ret);
	}

	hsotg->delayed_status = false;
	if (ret == USB_GADGET_DELAYED_STATUS)
		hsotg->delayed_status = true;

	/*
	 * the request is either unhandlable, or is not formatted correctly
	 * so respond with a STALL for the status stage to indicate failure.
	 */

	if (ret < 0)
		dwc2_hsotg_stall_ep0(hsotg);
}