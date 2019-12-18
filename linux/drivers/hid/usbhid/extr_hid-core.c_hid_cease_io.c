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
struct usbhid_device {int /*<<< orphan*/  urbout; int /*<<< orphan*/  urbctrl; int /*<<< orphan*/  urbin; int /*<<< orphan*/  io_retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hid_cease_io(struct usbhid_device *usbhid)
{
	del_timer_sync(&usbhid->io_retry);
	usb_kill_urb(usbhid->urbin);
	usb_kill_urb(usbhid->urbctrl);
	usb_kill_urb(usbhid->urbout);
}