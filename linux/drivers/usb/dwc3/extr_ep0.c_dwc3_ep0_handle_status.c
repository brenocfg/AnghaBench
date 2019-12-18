#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct usb_ctrlrequest {scalar_t__ bRequestType; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct dwc3_ep {int flags; } ;
struct TYPE_5__ {int length; int /*<<< orphan*/  complete; scalar_t__ buf; } ;
struct TYPE_6__ {TYPE_2__ request; struct dwc3_ep* dep; } ;
struct TYPE_4__ {int is_selfpowered; } ;
struct dwc3 {TYPE_3__ ep0_usb_req; scalar_t__ setup_buf; struct dwc3_ep** eps; int /*<<< orphan*/  regs; int /*<<< orphan*/  speed; TYPE_1__ gadget; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 scalar_t__ DWC3_DCTL_INITU1ENA ; 
 scalar_t__ DWC3_DCTL_INITU2ENA ; 
 int /*<<< orphan*/  DWC3_DSTS_SUPERSPEED ; 
 int /*<<< orphan*/  DWC3_DSTS_SUPERSPEED_PLUS ; 
 int DWC3_EP_STALL ; 
 int EINVAL ; 
 int USB_DEV_STAT_U1_ENABLED ; 
 int USB_DEV_STAT_U2_ENABLED ; 
 int USB_ENDPOINT_HALT ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 scalar_t__ USB_RECIP_MASK ; 
 int __dwc3_gadget_ep0_queue (struct dwc3_ep*,TYPE_3__*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dwc3_ep0_status_cmpl ; 
 scalar_t__ dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dwc3_ep* dwc3_wIndex_to_dep (struct dwc3*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_handle_status(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl)
{
	struct dwc3_ep		*dep;
	u32			recip;
	u32			value;
	u32			reg;
	u16			usb_status = 0;
	__le16			*response_pkt;

	/* We don't support PTM_STATUS */
	value = le16_to_cpu(ctrl->wValue);
	if (value != 0)
		return -EINVAL;

	recip = ctrl->bRequestType & USB_RECIP_MASK;
	switch (recip) {
	case USB_RECIP_DEVICE:
		/*
		 * LTM will be set once we know how to set this in HW.
		 */
		usb_status |= dwc->gadget.is_selfpowered;

		if ((dwc->speed == DWC3_DSTS_SUPERSPEED) ||
		    (dwc->speed == DWC3_DSTS_SUPERSPEED_PLUS)) {
			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			if (reg & DWC3_DCTL_INITU1ENA)
				usb_status |= 1 << USB_DEV_STAT_U1_ENABLED;
			if (reg & DWC3_DCTL_INITU2ENA)
				usb_status |= 1 << USB_DEV_STAT_U2_ENABLED;
		}

		break;

	case USB_RECIP_INTERFACE:
		/*
		 * Function Remote Wake Capable	D0
		 * Function Remote Wakeup	D1
		 */
		break;

	case USB_RECIP_ENDPOINT:
		dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
		if (!dep)
			return -EINVAL;

		if (dep->flags & DWC3_EP_STALL)
			usb_status = 1 << USB_ENDPOINT_HALT;
		break;
	default:
		return -EINVAL;
	}

	response_pkt = (__le16 *) dwc->setup_buf;
	*response_pkt = cpu_to_le16(usb_status);

	dep = dwc->eps[0];
	dwc->ep0_usb_req.dep = dep;
	dwc->ep0_usb_req.request.length = sizeof(*response_pkt);
	dwc->ep0_usb_req.request.buf = dwc->setup_buf;
	dwc->ep0_usb_req.request.complete = dwc3_ep0_status_cmpl;

	return __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_req);
}