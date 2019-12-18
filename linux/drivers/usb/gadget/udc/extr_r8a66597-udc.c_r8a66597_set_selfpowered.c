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
struct usb_gadget {int is_selfpowered; } ;
struct r8a66597 {int device_status; } ;

/* Variables and functions */
 int USB_DEVICE_SELF_POWERED ; 
 struct r8a66597* gadget_to_r8a66597 (struct usb_gadget*) ; 

__attribute__((used)) static int r8a66597_set_selfpowered(struct usb_gadget *gadget, int is_self)
{
	struct r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);

	gadget->is_selfpowered = (is_self != 0);
	if (is_self)
		r8a66597->device_status |= 1 << USB_DEVICE_SELF_POWERED;
	else
		r8a66597->device_status &= ~(1 << USB_DEVICE_SELF_POWERED);

	return 0;
}