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
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_SET_CONFIGURATION ; 
 int USB_TYPE_CLASS ; 
 scalar_t__ kone_check_write (struct usb_device*) ; 
 int /*<<< orphan*/  kone_command_profile ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kone_set_profile(struct usb_device *usb_dev,
		struct kone_profile const *profile, int number)
{
	int len;

	if (number < 1 || number > 5)
		return -EINVAL;

	len = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			USB_REQ_SET_CONFIGURATION,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT,
			kone_command_profile, number, (void *)profile,
			sizeof(struct kone_profile),
			USB_CTRL_SET_TIMEOUT);

	if (len != sizeof(struct kone_profile))
		return len;

	if (kone_check_write(usb_dev))
		return -EIO;

	return 0;
}