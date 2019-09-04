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
struct usb_device {int dummy; } ;
struct redrat3_dev {int /*<<< orphan*/  led; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redrat3_delete (struct redrat3_dev*,struct usb_device*) ; 
 struct redrat3_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void redrat3_dev_disconnect(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct redrat3_dev *rr3 = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	rc_unregister_device(rr3->rc);
	led_classdev_unregister(&rr3->led);
	redrat3_delete(rr3, udev);
}