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
typedef  int /*<<< orphan*/  u32 ;
struct usb_ctrlrequest {scalar_t__ wLength; int bRequestType; int bRequest; } ;
struct nbu2ss_udc {scalar_t__ ep0state; int /*<<< orphan*/  lock; struct usb_ctrlrequest ctrl; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EP0_IDLE ; 
 scalar_t__ EP0_IN_DATA_PHASE ; 
 scalar_t__ EP0_IN_STATUS_PHASE ; 
 scalar_t__ EP0_OUT_DATA_PHASE ; 
 int EP0_send_NULL (struct nbu2ss_udc*,int) ; 
 int USB_DIR_IN ; 
#define  USB_REQ_CLEAR_FEATURE 132 
#define  USB_REQ_GET_STATUS 131 
#define  USB_REQ_SET_ADDRESS 130 
#define  USB_REQ_SET_CONFIGURATION 129 
#define  USB_REQ_SET_FEATURE 128 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  _nbu2ss_read_request_data (struct nbu2ss_udc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int std_req_clear_feature (struct nbu2ss_udc*) ; 
 int std_req_get_status (struct nbu2ss_udc*) ; 
 int std_req_set_address (struct nbu2ss_udc*) ; 
 int std_req_set_configuration (struct nbu2ss_udc*) ; 
 int std_req_set_feature (struct nbu2ss_udc*) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static inline int _nbu2ss_decode_request(struct nbu2ss_udc *udc)
{
	bool			bcall_back = true;
	int			nret = -EINVAL;
	struct usb_ctrlrequest	*p_ctrl;

	p_ctrl = &udc->ctrl;
	_nbu2ss_read_request_data(udc, (u32 *)p_ctrl);

	/* ep0 state control */
	if (p_ctrl->wLength == 0) {
		udc->ep0state = EP0_IN_STATUS_PHASE;

	} else {
		if (p_ctrl->bRequestType & USB_DIR_IN)
			udc->ep0state = EP0_IN_DATA_PHASE;
		else
			udc->ep0state = EP0_OUT_DATA_PHASE;
	}

	if ((p_ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		switch (p_ctrl->bRequest) {
		case USB_REQ_GET_STATUS:
			nret = std_req_get_status(udc);
			bcall_back = false;
			break;

		case USB_REQ_CLEAR_FEATURE:
			nret = std_req_clear_feature(udc);
			bcall_back = false;
			break;

		case USB_REQ_SET_FEATURE:
			nret = std_req_set_feature(udc);
			bcall_back = false;
			break;

		case USB_REQ_SET_ADDRESS:
			nret = std_req_set_address(udc);
			bcall_back = false;
			break;

		case USB_REQ_SET_CONFIGURATION:
			nret = std_req_set_configuration(udc);
			break;

		default:
			break;
		}
	}

	if (!bcall_back) {
		if (udc->ep0state == EP0_IN_STATUS_PHASE) {
			if (nret >= 0) {
				/*--------------------------------------*/
				/* Status Stage */
				nret = EP0_send_NULL(udc, true);
			}
		}

	} else {
		spin_unlock(&udc->lock);
		nret = udc->driver->setup(&udc->gadget, &udc->ctrl);
		spin_lock(&udc->lock);
	}

	if (nret < 0)
		udc->ep0state = EP0_IDLE;

	return nret;
}