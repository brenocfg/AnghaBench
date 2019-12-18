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
struct usb_function {scalar_t__ bind_deactivated; int /*<<< orphan*/  (* unbind ) (struct usb_configuration*,struct usb_function*) ;int /*<<< orphan*/  list; int /*<<< orphan*/  endpoints; int /*<<< orphan*/  (* disable ) (struct usb_function*) ;} ;
struct usb_configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_function*) ; 
 int /*<<< orphan*/  stub2 (struct usb_configuration*,struct usb_function*) ; 
 int /*<<< orphan*/  usb_function_activate (struct usb_function*) ; 

void usb_remove_function(struct usb_configuration *c, struct usb_function *f)
{
	if (f->disable)
		f->disable(f);

	bitmap_zero(f->endpoints, 32);
	list_del(&f->list);
	if (f->unbind)
		f->unbind(c, f);

	if (f->bind_deactivated)
		usb_function_activate(f);
}