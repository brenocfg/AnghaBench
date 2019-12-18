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
struct usb_function {struct usb_descriptor_header** fs_descriptors; struct usb_descriptor_header** hs_descriptors; struct usb_descriptor_header** ss_descriptors; struct usb_descriptor_header** ssp_descriptors; } ;
struct usb_descriptor_header {int dummy; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_SUPER_PLUS 128 

__attribute__((used)) static struct usb_descriptor_header **
function_descriptors(struct usb_function *f,
		     enum usb_device_speed speed)
{
	struct usb_descriptor_header **descriptors;

	/*
	 * NOTE: we try to help gadget drivers which might not be setting
	 * max_speed appropriately.
	 */

	switch (speed) {
	case USB_SPEED_SUPER_PLUS:
		descriptors = f->ssp_descriptors;
		if (descriptors)
			break;
		/* FALLTHROUGH */
	case USB_SPEED_SUPER:
		descriptors = f->ss_descriptors;
		if (descriptors)
			break;
		/* FALLTHROUGH */
	case USB_SPEED_HIGH:
		descriptors = f->hs_descriptors;
		if (descriptors)
			break;
		/* FALLTHROUGH */
	default:
		descriptors = f->fs_descriptors;
	}

	/*
	 * if we can't find any descriptors at all, then this gadget deserves to
	 * Oops with a NULL pointer dereference
	 */

	return descriptors;
}