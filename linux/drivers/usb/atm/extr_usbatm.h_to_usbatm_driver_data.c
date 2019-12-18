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
struct usbatm_data {void* driver_data; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 struct usbatm_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static inline void *to_usbatm_driver_data(struct usb_interface *intf)
{
	struct usbatm_data *usbatm_instance;

	if (intf == NULL)
		return NULL;

	usbatm_instance = usb_get_intfdata(intf);

	if (usbatm_instance == NULL) /* set NULL before unbind() */
		return NULL;

	return usbatm_instance->driver_data; /* set NULL after unbind() */
}