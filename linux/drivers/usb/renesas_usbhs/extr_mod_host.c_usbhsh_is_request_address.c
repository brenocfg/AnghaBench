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
struct usb_ctrlrequest {scalar_t__ bRequestType; scalar_t__ bRequest; } ;
struct urb {scalar_t__ setup_packet; } ;

/* Variables and functions */
 scalar_t__ DeviceOutRequest ; 
 scalar_t__ USB_REQ_SET_ADDRESS ; 

__attribute__((used)) static int usbhsh_is_request_address(struct urb *urb)
{
	struct usb_ctrlrequest *req;

	req = (struct usb_ctrlrequest *)urb->setup_packet;

	if ((DeviceOutRequest    == req->bRequestType << 8) &&
	    (USB_REQ_SET_ADDRESS == req->bRequest))
		return 1;
	else
		return 0;
}