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
struct usb_ctrlrequest {int bRequestType; int bRequest; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 134 
#define  USB_REQ_GET_STATUS 133 
#define  USB_REQ_SET_ADDRESS 132 
#define  USB_REQ_SET_CONFIGURATION 131 
#define  USB_REQ_SET_FEATURE 130 
#define  USB_REQ_SET_ISOCH_DELAY 129 
#define  USB_REQ_SET_SEL 128 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  usb3_set_p0_con_stall (struct renesas_usb3*) ; 
 int usb3_std_req_feature (struct renesas_usb3*,struct usb_ctrlrequest*,int) ; 
 int usb3_std_req_get_status (struct renesas_usb3*,struct usb_ctrlrequest*) ; 
 int usb3_std_req_set_address (struct renesas_usb3*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usb3_std_req_set_configuration (struct renesas_usb3*,struct usb_ctrlrequest*) ; 
 int usb3_std_req_set_sel (struct renesas_usb3*,struct usb_ctrlrequest*) ; 

__attribute__((used)) static bool usb3_handle_standard_request(struct renesas_usb3 *usb3,
					 struct usb_ctrlrequest *ctrl)
{
	bool ret = false;
	bool stall = false;

	if ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		switch (ctrl->bRequest) {
		case USB_REQ_SET_ADDRESS:
			stall = usb3_std_req_set_address(usb3, ctrl);
			ret = true;
			break;
		case USB_REQ_GET_STATUS:
			stall = usb3_std_req_get_status(usb3, ctrl);
			ret = true;
			break;
		case USB_REQ_CLEAR_FEATURE:
			stall = usb3_std_req_feature(usb3, ctrl, false);
			ret = true;
			break;
		case USB_REQ_SET_FEATURE:
			stall = usb3_std_req_feature(usb3, ctrl, true);
			ret = true;
			break;
		case USB_REQ_SET_SEL:
			stall = usb3_std_req_set_sel(usb3, ctrl);
			ret = true;
			break;
		case USB_REQ_SET_ISOCH_DELAY:
			/* This hardware doesn't support Isochronous xfer */
			stall = true;
			ret = true;
			break;
		case USB_REQ_SET_CONFIGURATION:
			usb3_std_req_set_configuration(usb3, ctrl);
			break;
		default:
			break;
		}
	}

	if (stall)
		usb3_set_p0_con_stall(usb3);

	return ret;
}