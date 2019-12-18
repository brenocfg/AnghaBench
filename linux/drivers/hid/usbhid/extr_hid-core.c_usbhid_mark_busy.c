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
struct usbhid_device {struct usb_interface* intf; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhid_mark_busy(struct usbhid_device *usbhid)
{
	struct usb_interface *intf = usbhid->intf;

	usb_mark_last_busy(interface_to_usbdev(intf));
}