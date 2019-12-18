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
struct usb_ctrlrequest {int bRequestType; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  usb3_set_p0_con_for_no_data (struct renesas_usb3*) ; 
 int usb3_std_req_feature_device (struct renesas_usb3*,struct usb_ctrlrequest*,int) ; 
 int usb3_std_req_feature_endpoint (struct renesas_usb3*,struct usb_ctrlrequest*,int) ; 

__attribute__((used)) static bool usb3_std_req_feature(struct renesas_usb3 *usb3,
				 struct usb_ctrlrequest *ctrl, bool set)
{
	bool stall = false;

	switch (ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		stall = usb3_std_req_feature_device(usb3, ctrl, set);
		break;
	case USB_RECIP_INTERFACE:
		break;
	case USB_RECIP_ENDPOINT:
		stall = usb3_std_req_feature_endpoint(usb3, ctrl, set);
		break;
	default:
		stall = true;
		break;
	}

	if (!stall)
		usb3_set_p0_con_for_no_data(usb3);

	return stall;
}