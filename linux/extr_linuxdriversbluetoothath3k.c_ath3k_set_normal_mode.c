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

/* Variables and functions */
 unsigned char ATH3K_MODE_MASK ; 
 unsigned char ATH3K_NORMAL_MODE ; 
 int /*<<< orphan*/  ATH3K_SET_NORMAL_MODE ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_TYPE_VENDOR ; 
 int ath3k_get_state (struct usb_device*,unsigned char*) ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath3k_set_normal_mode(struct usb_device *udev)
{
	unsigned char fw_state;
	int pipe = 0, ret;

	ret = ath3k_get_state(udev, &fw_state);
	if (ret < 0) {
		BT_ERR("Can't get state to change to normal mode err");
		return ret;
	}

	if ((fw_state & ATH3K_MODE_MASK) == ATH3K_NORMAL_MODE) {
		BT_DBG("firmware was already in normal mode");
		return 0;
	}

	pipe = usb_sndctrlpipe(udev, 0);
	return usb_control_msg(udev, pipe, ATH3K_SET_NORMAL_MODE,
			USB_TYPE_VENDOR, 0, 0,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
}