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
struct igorplugusb {int /*<<< orphan*/  urb; int /*<<< orphan*/  timer; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct igorplugusb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igorplugusb_disconnect(struct usb_interface *intf)
{
	struct igorplugusb *ir = usb_get_intfdata(intf);

	rc_unregister_device(ir->rc);
	del_timer_sync(&ir->timer);
	usb_set_intfdata(intf, NULL);
	usb_kill_urb(ir->urb);
	usb_free_urb(ir->urb);
}