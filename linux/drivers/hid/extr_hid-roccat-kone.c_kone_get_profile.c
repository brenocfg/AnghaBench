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
struct usb_device {int dummy; } ;
struct kone_profile {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_CLEAR_FEATURE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  kone_command_profile ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct kone_profile*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kone_get_profile(struct usb_device *usb_dev,
		struct kone_profile *buf, int number)
{
	int len;

	if (number < 1 || number > 5)
		return -EINVAL;

	len = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			USB_REQ_CLEAR_FEATURE,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			kone_command_profile, number, buf,
			sizeof(struct kone_profile), USB_CTRL_SET_TIMEOUT);

	if (len != sizeof(struct kone_profile))
		return -EIO;

	return 0;
}