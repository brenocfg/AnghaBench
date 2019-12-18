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
typedef  char u8 ;
struct usb_ctrlrequest {int bRequest; int /*<<< orphan*/  bRequestType; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/  actual_length; scalar_t__ transfer_buffer; } ;
struct dummy_hcd {struct dummy* dum; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dummy_ep {int halted; int /*<<< orphan*/  wedged; TYPE_2__ ep; } ;
struct TYPE_4__ {int b_hnp_enable; int a_hnp_support; int a_alt_hnp_support; } ;
struct dummy {unsigned int address; int devstatus; TYPE_1__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  Dev_InRequest ; 
 int /*<<< orphan*/  Dev_Request ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  Ep_InRequest ; 
 int /*<<< orphan*/  Ep_Request ; 
 int /*<<< orphan*/  HCD_USB3 ; 
 int /*<<< orphan*/  Intf_InRequest ; 
#define  USB_DEVICE_A_ALT_HNP_SUPPORT 138 
#define  USB_DEVICE_A_HNP_SUPPORT 137 
#define  USB_DEVICE_B_HNP_ENABLE 136 
#define  USB_DEVICE_LTM_ENABLE 135 
#define  USB_DEVICE_REMOTE_WAKEUP 134 
#define  USB_DEVICE_U1_ENABLE 133 
#define  USB_DEVICE_U2_ENABLE 132 
 unsigned int USB_DEV_STAT_LTM_ENABLED ; 
 unsigned int USB_DEV_STAT_U1_ENABLED ; 
 unsigned int USB_DEV_STAT_U2_ENABLED ; 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
#define  USB_REQ_SET_FEATURE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_3__* dummy_hcd_to_hcd (struct dummy_hcd*) ; 
 int /*<<< orphan*/  ep0name ; 
 struct dummy_ep* find_endpoint (struct dummy*,unsigned int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 

__attribute__((used)) static int handle_control_request(struct dummy_hcd *dum_hcd, struct urb *urb,
				  struct usb_ctrlrequest *setup,
				  int *status)
{
	struct dummy_ep		*ep2;
	struct dummy		*dum = dum_hcd->dum;
	int			ret_val = 1;
	unsigned	w_index;
	unsigned	w_value;

	w_index = le16_to_cpu(setup->wIndex);
	w_value = le16_to_cpu(setup->wValue);
	switch (setup->bRequest) {
	case USB_REQ_SET_ADDRESS:
		if (setup->bRequestType != Dev_Request)
			break;
		dum->address = w_value;
		*status = 0;
		dev_dbg(udc_dev(dum), "set_address = %d\n",
				w_value);
		ret_val = 0;
		break;
	case USB_REQ_SET_FEATURE:
		if (setup->bRequestType == Dev_Request) {
			ret_val = 0;
			switch (w_value) {
			case USB_DEVICE_REMOTE_WAKEUP:
				break;
			case USB_DEVICE_B_HNP_ENABLE:
				dum->gadget.b_hnp_enable = 1;
				break;
			case USB_DEVICE_A_HNP_SUPPORT:
				dum->gadget.a_hnp_support = 1;
				break;
			case USB_DEVICE_A_ALT_HNP_SUPPORT:
				dum->gadget.a_alt_hnp_support = 1;
				break;
			case USB_DEVICE_U1_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U1_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			case USB_DEVICE_U2_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U2_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			case USB_DEVICE_LTM_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_LTM_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			default:
				ret_val = -EOPNOTSUPP;
			}
			if (ret_val == 0) {
				dum->devstatus |= (1 << w_value);
				*status = 0;
			}
		} else if (setup->bRequestType == Ep_Request) {
			/* endpoint halt */
			ep2 = find_endpoint(dum, w_index);
			if (!ep2 || ep2->ep.name == ep0name) {
				ret_val = -EOPNOTSUPP;
				break;
			}
			ep2->halted = 1;
			ret_val = 0;
			*status = 0;
		}
		break;
	case USB_REQ_CLEAR_FEATURE:
		if (setup->bRequestType == Dev_Request) {
			ret_val = 0;
			switch (w_value) {
			case USB_DEVICE_REMOTE_WAKEUP:
				w_value = USB_DEVICE_REMOTE_WAKEUP;
				break;
			case USB_DEVICE_U1_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U1_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			case USB_DEVICE_U2_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U2_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			case USB_DEVICE_LTM_ENABLE:
				if (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_LTM_ENABLED;
				else
					ret_val = -EOPNOTSUPP;
				break;
			default:
				ret_val = -EOPNOTSUPP;
				break;
			}
			if (ret_val == 0) {
				dum->devstatus &= ~(1 << w_value);
				*status = 0;
			}
		} else if (setup->bRequestType == Ep_Request) {
			/* endpoint halt */
			ep2 = find_endpoint(dum, w_index);
			if (!ep2) {
				ret_val = -EOPNOTSUPP;
				break;
			}
			if (!ep2->wedged)
				ep2->halted = 0;
			ret_val = 0;
			*status = 0;
		}
		break;
	case USB_REQ_GET_STATUS:
		if (setup->bRequestType == Dev_InRequest
				|| setup->bRequestType == Intf_InRequest
				|| setup->bRequestType == Ep_InRequest) {
			char *buf;
			/*
			 * device: remote wakeup, selfpowered
			 * interface: nothing
			 * endpoint: halt
			 */
			buf = (char *)urb->transfer_buffer;
			if (urb->transfer_buffer_length > 0) {
				if (setup->bRequestType == Ep_InRequest) {
					ep2 = find_endpoint(dum, w_index);
					if (!ep2) {
						ret_val = -EOPNOTSUPP;
						break;
					}
					buf[0] = ep2->halted;
				} else if (setup->bRequestType ==
					   Dev_InRequest) {
					buf[0] = (u8)dum->devstatus;
				} else
					buf[0] = 0;
			}
			if (urb->transfer_buffer_length > 1)
				buf[1] = 0;
			urb->actual_length = min_t(u32, 2,
				urb->transfer_buffer_length);
			ret_val = 0;
			*status = 0;
		}
		break;
	}
	return ret_val;
}