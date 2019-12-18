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
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct r8a66597 {int old_vbus; int /*<<< orphan*/  timer; int /*<<< orphan*/  scount; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  INTENB0 ; 
 int /*<<< orphan*/  INTSTS0 ; 
 int /*<<< orphan*/  R8A66597_MAX_SAMPLING ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  VBSE ; 
 int VBSTS ; 
 struct r8a66597* gadget_to_r8a66597 (struct usb_gadget*) ; 
 int /*<<< orphan*/  init_controller (struct r8a66597*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_start_xclock (struct r8a66597*) ; 

__attribute__((used)) static int r8a66597_start(struct usb_gadget *gadget,
		struct usb_gadget_driver *driver)
{
	struct r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);

	if (!driver
			|| driver->max_speed < USB_SPEED_HIGH
			|| !driver->setup)
		return -EINVAL;
	if (!r8a66597)
		return -ENODEV;

	/* hook up the driver */
	r8a66597->driver = driver;

	init_controller(r8a66597);
	r8a66597_bset(r8a66597, VBSE, INTENB0);
	if (r8a66597_read(r8a66597, INTSTS0) & VBSTS) {
		r8a66597_start_xclock(r8a66597);
		/* start vbus sampling */
		r8a66597->old_vbus = r8a66597_read(r8a66597,
					 INTSTS0) & VBSTS;
		r8a66597->scount = R8A66597_MAX_SAMPLING;
		mod_timer(&r8a66597->timer, jiffies + msecs_to_jiffies(50));
	}

	return 0;
}