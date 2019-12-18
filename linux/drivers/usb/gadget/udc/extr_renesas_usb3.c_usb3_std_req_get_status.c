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
typedef  int u16 ;
typedef  int /*<<< orphan*/  tx_data ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wIndex; } ;
struct renesas_usb3_ep {int /*<<< orphan*/  halt; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  is_selfpowered; } ;
struct renesas_usb3 {int /*<<< orphan*/  ep0_req; TYPE_1__ gadget; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int USB_DEVICE_SELF_POWERED ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb3_feature_get_un_enabled (struct renesas_usb3*) ; 
 struct renesas_usb3_ep* usb3_get_ep (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_pipe0_get_status_completion ; 
 int /*<<< orphan*/  usb3_pipe0_internal_xfer (struct renesas_usb3*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_to_dev (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb_req_to_usb3_req (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool usb3_std_req_get_status(struct renesas_usb3 *usb3,
				    struct usb_ctrlrequest *ctrl)
{
	bool stall = false;
	struct renesas_usb3_ep *usb3_ep;
	int num;
	u16 status = 0;
	__le16 tx_data;

	switch (ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		if (usb3->gadget.is_selfpowered)
			status |= 1 << USB_DEVICE_SELF_POWERED;
		if (usb3->gadget.speed == USB_SPEED_SUPER)
			status |= usb3_feature_get_un_enabled(usb3);
		break;
	case USB_RECIP_INTERFACE:
		break;
	case USB_RECIP_ENDPOINT:
		num = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		usb3_ep = usb3_get_ep(usb3, num);
		if (usb3_ep->halt)
			status |= 1 << USB_ENDPOINT_HALT;
		break;
	default:
		stall = true;
		break;
	}

	if (!stall) {
		tx_data = cpu_to_le16(status);
		dev_dbg(usb3_to_dev(usb3), "get_status: req = %p\n",
			usb_req_to_usb3_req(usb3->ep0_req));
		usb3_pipe0_internal_xfer(usb3, &tx_data, sizeof(tx_data),
					 usb3_pipe0_get_status_completion);
	}

	return stall;
}