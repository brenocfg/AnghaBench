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
struct usb_gadget {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int speed; } ;
struct dummy {TYPE_1__ gadget; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_udc_update_ep0 (struct dummy*) ; 
 struct dummy* gadget_dev_to_dummy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dummy_udc_set_speed(struct usb_gadget *_gadget,
		enum usb_device_speed speed)
{
	struct dummy	*dum;

	dum = gadget_dev_to_dummy(&_gadget->dev);
	dum->gadget.speed = speed;
	dummy_udc_update_ep0(dum);
}