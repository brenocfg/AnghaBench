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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct stk1160 {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk1160_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stk1160_read_reg(struct stk1160 *dev, u16 reg, u8 *value)
{
	int ret;
	int pipe = usb_rcvctrlpipe(dev->udev, 0);
	u8 *buf;

	*value = 0;

	buf = kmalloc(sizeof(u8), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	ret = usb_control_msg(dev->udev, pipe, 0x00,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00, reg, buf, sizeof(u8), HZ);
	if (ret < 0) {
		stk1160_err("read failed on reg 0x%x (%d)\n",
			reg, ret);
		kfree(buf);
		return ret;
	}

	*value = *buf;
	kfree(buf);
	return 0;
}