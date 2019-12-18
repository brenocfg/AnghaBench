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
struct usbatm_data {struct usb_device* usb_dev; } ;
struct usb_device {int dummy; } ;
struct speedtch_instance_data {struct usbatm_data* usbatm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_TIMEOUT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dbg (struct usbatm_data*,char*,char*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_warn (struct usbatm_data*,char*,char*,int) ; 

__attribute__((used)) static void speedtch_set_swbuff(struct speedtch_instance_data *instance, int state)
{
	struct usbatm_data *usbatm = instance->usbatm;
	struct usb_device *usb_dev = usbatm->usb_dev;
	int ret;

	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x32, 0x40, state ? 0x01 : 0x00, 0x00, NULL, 0, CTRL_TIMEOUT);
	if (ret < 0)
		usb_warn(usbatm,
			 "%sabling SW buffering: usb_control_msg returned %d\n",
			 state ? "En" : "Dis", ret);
	else
		usb_dbg(usbatm, "speedtch_set_swbuff: %sbled SW buffering\n", state ? "En" : "Dis");
}