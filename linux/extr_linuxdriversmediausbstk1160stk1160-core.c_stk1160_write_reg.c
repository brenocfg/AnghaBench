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
typedef  int /*<<< orphan*/  u16 ;
struct stk1160 {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  stk1160_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stk1160_write_reg(struct stk1160 *dev, u16 reg, u16 value)
{
	int ret;
	int pipe = usb_sndctrlpipe(dev->udev, 0);

	ret =  usb_control_msg(dev->udev, pipe, 0x01,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, reg, NULL, 0, HZ);
	if (ret < 0) {
		stk1160_err("write failed on reg 0x%x (%d)\n",
			reg, ret);
		return ret;
	}

	return 0;
}