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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct usb_request {scalar_t__ context; } ;
struct usb_ep {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; scalar_t__ bRequest; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct nbu2ss_udc {struct usb_ctrlrequest ctrl; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_TEST_MODE ; 
 scalar_t__ USB_RECIP_DEVICE ; 
 int USB_RECIP_MASK ; 
 scalar_t__ USB_REQ_SET_FEATURE ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  _nbu2ss_set_test_mode (struct nbu2ss_udc*,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _nbu2ss_ep0_complete(struct usb_ep *_ep, struct usb_request *_req)
{
	u8		recipient;
	u16		selector;
	u16		wIndex;
	u32		test_mode;
	struct usb_ctrlrequest	*p_ctrl;
	struct nbu2ss_udc *udc;

	if (!_ep || !_req)
		return;

	udc = (struct nbu2ss_udc *)_req->context;
	p_ctrl = &udc->ctrl;
	if ((p_ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		if (p_ctrl->bRequest == USB_REQ_SET_FEATURE) {
			/*-------------------------------------------------*/
			/* SET_FEATURE */
			recipient = (u8)(p_ctrl->bRequestType & USB_RECIP_MASK);
			selector  = le16_to_cpu(p_ctrl->wValue);
			if ((recipient == USB_RECIP_DEVICE) &&
			    (selector == USB_DEVICE_TEST_MODE)) {
				wIndex = le16_to_cpu(p_ctrl->wIndex);
				test_mode = (u32)(wIndex >> 8);
				_nbu2ss_set_test_mode(udc, test_mode);
			}
		}
	}
}