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
typedef  int u32 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct dwc3_ep {int flags; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int DWC3_EP_WEDGE ; 
 int EINVAL ; 
#define  USB_ENDPOINT_HALT 128 
 int __dwc3_gadget_ep_set_halt (struct dwc3_ep*,int,int) ; 
 struct dwc3_ep* dwc3_wIndex_to_dep (struct dwc3*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_handle_endpoint(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl, int set)
{
	struct dwc3_ep		*dep;
	u32			wValue;
	int			ret;

	wValue = le16_to_cpu(ctrl->wValue);

	switch (wValue) {
	case USB_ENDPOINT_HALT:
		dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
		if (!dep)
			return -EINVAL;

		if (set == 0 && (dep->flags & DWC3_EP_WEDGE))
			break;

		ret = __dwc3_gadget_ep_set_halt(dep, set, true);
		if (ret)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}