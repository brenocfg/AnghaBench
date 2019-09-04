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
struct powermate_device {int /*<<< orphan*/  config; int /*<<< orphan*/  irq; int /*<<< orphan*/  input; scalar_t__ requires_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct powermate_device*) ; 
 int /*<<< orphan*/  powermate_free_buffers (int /*<<< orphan*/ ,struct powermate_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct powermate_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void powermate_disconnect(struct usb_interface *intf)
{
	struct powermate_device *pm = usb_get_intfdata (intf);

	usb_set_intfdata(intf, NULL);
	if (pm) {
		pm->requires_update = 0;
		usb_kill_urb(pm->irq);
		input_unregister_device(pm->input);
		usb_free_urb(pm->irq);
		usb_free_urb(pm->config);
		powermate_free_buffers(interface_to_usbdev(intf), pm);

		kfree(pm);
	}
}