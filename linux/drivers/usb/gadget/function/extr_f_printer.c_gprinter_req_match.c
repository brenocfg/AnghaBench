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
typedef  int u16 ;
struct usb_function {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct printer_dev {int interface; } ;

/* Variables and functions */
#define  GET_DEVICE_ID 130 
#define  GET_PORT_STATUS 129 
#define  SOFT_RESET 128 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_RECIP_MASK ; 
 int USB_TYPE_CLASS ; 
 int USB_TYPE_MASK ; 
 struct printer_dev* func_to_printer (struct usb_function*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gprinter_req_match(struct usb_function *f,
			       const struct usb_ctrlrequest *ctrl,
			       bool config0)
{
	struct printer_dev	*dev = func_to_printer(f);
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	if (config0)
		return false;

	if ((ctrl->bRequestType & USB_RECIP_MASK) != USB_RECIP_INTERFACE ||
	    (ctrl->bRequestType & USB_TYPE_MASK) != USB_TYPE_CLASS)
		return false;

	switch (ctrl->bRequest) {
	case GET_DEVICE_ID:
		w_index >>= 8;
		if (USB_DIR_IN & ctrl->bRequestType)
			break;
		return false;
	case GET_PORT_STATUS:
		if (!w_value && w_length == 1 &&
		    (USB_DIR_IN & ctrl->bRequestType))
			break;
		return false;
	case SOFT_RESET:
		if (!w_value && !w_length &&
		   !(USB_DIR_IN & ctrl->bRequestType))
			break;
		/* fall through */
	default:
		return false;
	}
	return w_index == dev->interface;
}