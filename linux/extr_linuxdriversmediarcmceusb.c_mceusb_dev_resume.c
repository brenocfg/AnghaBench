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
struct mceusb_dev {int /*<<< orphan*/  urb_in; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct mceusb_dev* usb_get_intfdata (struct usb_interface*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mceusb_dev_resume(struct usb_interface *intf)
{
	struct mceusb_dev *ir = usb_get_intfdata(intf);
	dev_info(ir->dev, "resume");
	if (usb_submit_urb(ir->urb_in, GFP_ATOMIC))
		return -EIO;
	return 0;
}