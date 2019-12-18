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
typedef  int /*<<< orphan*/  u32 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct TYPE_2__ {int state; } ;
struct dwc3 {TYPE_1__ gadget; int /*<<< orphan*/  regs; int /*<<< orphan*/  dis_u2_entry_quirk; int /*<<< orphan*/  dis_u1_entry_quirk; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int /*<<< orphan*/  DWC3_DCTL_ACCEPTU1ENA ; 
 int /*<<< orphan*/  DWC3_DCTL_ACCEPTU2ENA ; 
 int EINVAL ; 
 int USB_GADGET_DELAYED_STATUS ; 
#define  USB_STATE_ADDRESS 130 
#define  USB_STATE_CONFIGURED 129 
#define  USB_STATE_DEFAULT 128 
 int dwc3_ep0_delegate_req (struct dwc3*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_1__*,int const) ; 

__attribute__((used)) static int dwc3_ep0_set_config(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	enum usb_device_state state = dwc->gadget.state;
	u32 cfg;
	int ret;
	u32 reg;

	cfg = le16_to_cpu(ctrl->wValue);

	switch (state) {
	case USB_STATE_DEFAULT:
		return -EINVAL;

	case USB_STATE_ADDRESS:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		/* if the cfg matches and the cfg is non zero */
		if (cfg && (!ret || (ret == USB_GADGET_DELAYED_STATUS))) {

			/*
			 * only change state if set_config has already
			 * been processed. If gadget driver returns
			 * USB_GADGET_DELAYED_STATUS, we will wait
			 * to change the state on the next usb_ep_queue()
			 */
			if (ret == 0)
				usb_gadget_set_state(&dwc->gadget,
						USB_STATE_CONFIGURED);

			/*
			 * Enable transition to U1/U2 state when
			 * nothing is pending from application.
			 */
			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			if (!dwc->dis_u1_entry_quirk)
				reg |= DWC3_DCTL_ACCEPTU1ENA;
			if (!dwc->dis_u2_entry_quirk)
				reg |= DWC3_DCTL_ACCEPTU2ENA;
			dwc3_writel(dwc->regs, DWC3_DCTL, reg);
		}
		break;

	case USB_STATE_CONFIGURED:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		if (!cfg && !ret)
			usb_gadget_set_state(&dwc->gadget,
					USB_STATE_ADDRESS);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}