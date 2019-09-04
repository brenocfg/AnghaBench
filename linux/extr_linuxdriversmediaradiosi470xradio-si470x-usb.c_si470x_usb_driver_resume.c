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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct si470x_device {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int si470x_start_usb (struct si470x_device*) ; 
 struct si470x_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si470x_usb_driver_resume(struct usb_interface *intf)
{
	struct si470x_device *radio = usb_get_intfdata(intf);
	int ret;

	dev_info(&intf->dev, "resuming now...\n");

	/* start radio */
	ret = si470x_start_usb(radio);
	if (ret == 0)
		v4l2_ctrl_handler_setup(&radio->hdl);

	return ret;
}