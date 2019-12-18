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
struct usb_ctrlrequest {int bRequestType; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int dwc3_ep0_handle_device (struct dwc3*,struct usb_ctrlrequest*,int) ; 
 int dwc3_ep0_handle_endpoint (struct dwc3*,struct usb_ctrlrequest*,int) ; 
 int dwc3_ep0_handle_intf (struct dwc3*,struct usb_ctrlrequest*,int) ; 

__attribute__((used)) static int dwc3_ep0_handle_feature(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl, int set)
{
	u32			recip;
	int			ret;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	switch (recip) {
	case USB_RECIP_DEVICE:
		ret = dwc3_ep0_handle_device(dwc, ctrl, set);
		break;
	case USB_RECIP_INTERFACE:
		ret = dwc3_ep0_handle_intf(dwc, ctrl, set);
		break;
	case USB_RECIP_ENDPOINT:
		ret = dwc3_ep0_handle_endpoint(dwc, ctrl, set);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}