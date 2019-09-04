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
struct usb_interface {int dummy; } ;
struct imon {int /*<<< orphan*/  ir_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct imon* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imon_disconnect(struct usb_interface *intf)
{
	struct imon *imon = usb_get_intfdata(intf);

	usb_kill_urb(imon->ir_urb);
	usb_free_urb(imon->ir_urb);
}