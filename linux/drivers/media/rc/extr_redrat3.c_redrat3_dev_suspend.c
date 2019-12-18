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
struct redrat3_dev {int /*<<< orphan*/  flash_urb; int /*<<< orphan*/  wide_urb; int /*<<< orphan*/  narrow_urb; int /*<<< orphan*/  led; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_suspend (int /*<<< orphan*/ *) ; 
 struct redrat3_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redrat3_dev_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct redrat3_dev *rr3 = usb_get_intfdata(intf);

	led_classdev_suspend(&rr3->led);
	usb_kill_urb(rr3->narrow_urb);
	usb_kill_urb(rr3->wide_urb);
	usb_kill_urb(rr3->flash_urb);
	return 0;
}