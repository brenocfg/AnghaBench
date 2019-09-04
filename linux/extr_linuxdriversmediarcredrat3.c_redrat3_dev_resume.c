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
struct redrat3_dev {int /*<<< orphan*/  led; int /*<<< orphan*/  wide_urb; int /*<<< orphan*/  narrow_urb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  led_classdev_resume (int /*<<< orphan*/ *) ; 
 struct redrat3_dev* usb_get_intfdata (struct usb_interface*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redrat3_dev_resume(struct usb_interface *intf)
{
	struct redrat3_dev *rr3 = usb_get_intfdata(intf);

	if (usb_submit_urb(rr3->narrow_urb, GFP_ATOMIC))
		return -EIO;
	if (usb_submit_urb(rr3->wide_urb, GFP_ATOMIC))
		return -EIO;
	led_classdev_resume(&rr3->led);
	return 0;
}