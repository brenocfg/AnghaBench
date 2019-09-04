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
struct usb_kbd {int /*<<< orphan*/  led; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usb_kbd*) ; 
 struct usb_kbd* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kbd_free_mem (int /*<<< orphan*/ ,struct usb_kbd*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_kbd_disconnect(struct usb_interface *intf)
{
	struct usb_kbd *kbd = usb_get_intfdata (intf);

	usb_set_intfdata(intf, NULL);
	if (kbd) {
		usb_kill_urb(kbd->irq);
		input_unregister_device(kbd->dev);
		usb_kill_urb(kbd->led);
		usb_kbd_free_mem(interface_to_usbdev(intf), kbd);
		kfree(kbd);
	}
}