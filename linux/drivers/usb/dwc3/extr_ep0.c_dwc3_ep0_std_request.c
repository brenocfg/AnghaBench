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
struct usb_ctrlrequest {int bRequest; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 134 
#define  USB_REQ_GET_STATUS 133 
#define  USB_REQ_SET_ADDRESS 132 
#define  USB_REQ_SET_CONFIGURATION 131 
#define  USB_REQ_SET_FEATURE 130 
#define  USB_REQ_SET_ISOCH_DELAY 129 
#define  USB_REQ_SET_SEL 128 
 int dwc3_ep0_delegate_req (struct dwc3*,struct usb_ctrlrequest*) ; 
 int dwc3_ep0_handle_feature (struct dwc3*,struct usb_ctrlrequest*,int) ; 
 int dwc3_ep0_handle_status (struct dwc3*,struct usb_ctrlrequest*) ; 
 int dwc3_ep0_set_address (struct dwc3*,struct usb_ctrlrequest*) ; 
 int dwc3_ep0_set_config (struct dwc3*,struct usb_ctrlrequest*) ; 
 int dwc3_ep0_set_isoch_delay (struct dwc3*,struct usb_ctrlrequest*) ; 
 int dwc3_ep0_set_sel (struct dwc3*,struct usb_ctrlrequest*) ; 

__attribute__((used)) static int dwc3_ep0_std_request(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	int ret;

	switch (ctrl->bRequest) {
	case USB_REQ_GET_STATUS:
		ret = dwc3_ep0_handle_status(dwc, ctrl);
		break;
	case USB_REQ_CLEAR_FEATURE:
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 0);
		break;
	case USB_REQ_SET_FEATURE:
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 1);
		break;
	case USB_REQ_SET_ADDRESS:
		ret = dwc3_ep0_set_address(dwc, ctrl);
		break;
	case USB_REQ_SET_CONFIGURATION:
		ret = dwc3_ep0_set_config(dwc, ctrl);
		break;
	case USB_REQ_SET_SEL:
		ret = dwc3_ep0_set_sel(dwc, ctrl);
		break;
	case USB_REQ_SET_ISOCH_DELAY:
		ret = dwc3_ep0_set_isoch_delay(dwc, ctrl);
		break;
	default:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		break;
	}

	return ret;
}