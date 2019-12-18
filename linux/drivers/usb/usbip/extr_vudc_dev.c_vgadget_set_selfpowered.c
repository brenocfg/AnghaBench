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
struct vudc {int devstatus; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int USB_DEVICE_SELF_POWERED ; 
 struct vudc* usb_gadget_to_vudc (struct usb_gadget*) ; 

__attribute__((used)) static int vgadget_set_selfpowered(struct usb_gadget *_gadget, int value)
{
	struct vudc *udc = usb_gadget_to_vudc(_gadget);

	if (value)
		udc->devstatus |= (1 << USB_DEVICE_SELF_POWERED);
	else
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	return 0;
}