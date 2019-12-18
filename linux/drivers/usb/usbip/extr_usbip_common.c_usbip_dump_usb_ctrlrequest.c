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
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 138 
#define  USB_REQ_GET_CONFIGURATION 137 
#define  USB_REQ_GET_DESCRIPTOR 136 
#define  USB_REQ_GET_INTERFACE 135 
#define  USB_REQ_GET_STATUS 134 
#define  USB_REQ_SET_ADDRESS 133 
#define  USB_REQ_SET_CONFIGURATION 132 
#define  USB_REQ_SET_DESCRIPTOR 131 
#define  USB_REQ_SET_FEATURE 130 
#define  USB_REQ_SET_INTERFACE 129 
#define  USB_REQ_SYNCH_FRAME 128 
 int USB_TYPE_CLASS ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_RESERVED ; 
 int USB_TYPE_STANDARD ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  usbip_dump_request_type (int) ; 

__attribute__((used)) static void usbip_dump_usb_ctrlrequest(struct usb_ctrlrequest *cmd)
{
	if (!cmd) {
		pr_debug("       : null pointer\n");
		return;
	}

	pr_debug("       ");
	pr_debug("bRequestType(%02X) bRequest(%02X) wValue(%04X) wIndex(%04X) wLength(%04X) ",
		 cmd->bRequestType, cmd->bRequest,
		 cmd->wValue, cmd->wIndex, cmd->wLength);
	pr_debug("\n       ");

	if ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		pr_debug("STANDARD ");
		switch (cmd->bRequest) {
		case USB_REQ_GET_STATUS:
			pr_debug("GET_STATUS\n");
			break;
		case USB_REQ_CLEAR_FEATURE:
			pr_debug("CLEAR_FEAT\n");
			break;
		case USB_REQ_SET_FEATURE:
			pr_debug("SET_FEAT\n");
			break;
		case USB_REQ_SET_ADDRESS:
			pr_debug("SET_ADDRRS\n");
			break;
		case USB_REQ_GET_DESCRIPTOR:
			pr_debug("GET_DESCRI\n");
			break;
		case USB_REQ_SET_DESCRIPTOR:
			pr_debug("SET_DESCRI\n");
			break;
		case USB_REQ_GET_CONFIGURATION:
			pr_debug("GET_CONFIG\n");
			break;
		case USB_REQ_SET_CONFIGURATION:
			pr_debug("SET_CONFIG\n");
			break;
		case USB_REQ_GET_INTERFACE:
			pr_debug("GET_INTERF\n");
			break;
		case USB_REQ_SET_INTERFACE:
			pr_debug("SET_INTERF\n");
			break;
		case USB_REQ_SYNCH_FRAME:
			pr_debug("SYNC_FRAME\n");
			break;
		default:
			pr_debug("REQ(%02X)\n", cmd->bRequest);
			break;
		}
		usbip_dump_request_type(cmd->bRequestType);
	} else if ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_CLASS) {
		pr_debug("CLASS\n");
	} else if ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_VENDOR) {
		pr_debug("VENDOR\n");
	} else if ((cmd->bRequestType & USB_TYPE_MASK) == USB_TYPE_RESERVED) {
		pr_debug("RESERVED\n");
	}
}