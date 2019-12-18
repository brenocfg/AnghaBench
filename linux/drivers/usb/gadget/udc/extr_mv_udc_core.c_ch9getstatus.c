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
typedef  int u8 ;
typedef  int u16 ;
struct usb_ctrlrequest {int bRequestType; int wIndex; } ;
struct mv_udc {int remote_wakeup; int /*<<< orphan*/  ep0_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_STATE_XMIT ; 
 int EP_DIR_IN ; 
 int EP_DIR_OUT ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_DEVICE_SELF_POWERED ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_DIR_MASK ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_RECIP_MASK ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  ep0_stall (struct mv_udc*) ; 
 int ep_is_stall (struct mv_udc*,int,int) ; 
 int udc_prime_status (struct mv_udc*,int,int,int) ; 

__attribute__((used)) static void ch9getstatus(struct mv_udc *udc, u8 ep_num,
	struct usb_ctrlrequest *setup)
{
	u16 status = 0;
	int retval;

	if ((setup->bRequestType & (USB_DIR_IN | USB_TYPE_MASK))
		!= (USB_DIR_IN | USB_TYPE_STANDARD))
		return;

	if ((setup->bRequestType & USB_RECIP_MASK) == USB_RECIP_DEVICE) {
		status = 1 << USB_DEVICE_SELF_POWERED;
		status |= udc->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP;
	} else if ((setup->bRequestType & USB_RECIP_MASK)
			== USB_RECIP_INTERFACE) {
		/* get interface status */
		status = 0;
	} else if ((setup->bRequestType & USB_RECIP_MASK)
			== USB_RECIP_ENDPOINT) {
		u8 ep_num, direction;

		ep_num = setup->wIndex & USB_ENDPOINT_NUMBER_MASK;
		direction = (setup->wIndex & USB_ENDPOINT_DIR_MASK)
				? EP_DIR_IN : EP_DIR_OUT;
		status = ep_is_stall(udc, ep_num, direction)
				<< USB_ENDPOINT_HALT;
	}

	retval = udc_prime_status(udc, EP_DIR_IN, status, false);
	if (retval)
		ep0_stall(udc);
	else
		udc->ep0_state = DATA_STATE_XMIT;
}