#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_udc {TYPE_2__* gadget; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  max_speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* udc_set_speed ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static inline void usb_gadget_udc_set_speed(struct usb_udc *udc,
					    enum usb_device_speed speed)
{
	if (udc->gadget->ops->udc_set_speed) {
		enum usb_device_speed s;

		s = min(speed, udc->gadget->max_speed);
		udc->gadget->ops->udc_set_speed(udc->gadget, s);
	}
}