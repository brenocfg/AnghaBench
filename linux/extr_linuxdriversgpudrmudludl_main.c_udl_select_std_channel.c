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
typedef  int u8 ;
struct udl_device {int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  set_def_chn ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NR_USB_REQUEST_CHANNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int const*,int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udl_select_std_channel(struct udl_device *udl)
{
	int ret;
	static const u8 set_def_chn[] = {0x57, 0xCD, 0xDC, 0xA7,
					 0x1C, 0x88, 0x5E, 0x15,
					 0x60, 0xFE, 0xC6, 0x97,
					 0x16, 0x3D, 0x47, 0xF2};
	void *sendbuf;

	sendbuf = kmemdup(set_def_chn, sizeof(set_def_chn), GFP_KERNEL);
	if (!sendbuf)
		return -ENOMEM;

	ret = usb_control_msg(udl->udev,
			      usb_sndctrlpipe(udl->udev, 0),
			      NR_USB_REQUEST_CHANNEL,
			      (USB_DIR_OUT | USB_TYPE_VENDOR), 0, 0,
			      sendbuf, sizeof(set_def_chn),
			      USB_CTRL_SET_TIMEOUT);
	kfree(sendbuf);
	return ret < 0 ? ret : 0;
}