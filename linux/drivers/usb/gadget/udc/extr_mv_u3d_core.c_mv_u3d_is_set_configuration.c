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
struct usb_ctrlrequest {int bRequestType; scalar_t__ bRequest; } ;

/* Variables and functions */
 scalar_t__ USB_REQ_SET_CONFIGURATION ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 

__attribute__((used)) static int mv_u3d_is_set_configuration(struct usb_ctrlrequest *setup)
{
	if ((setup->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		if (setup->bRequest == USB_REQ_SET_CONFIGURATION)
			return 1;

	return 0;
}