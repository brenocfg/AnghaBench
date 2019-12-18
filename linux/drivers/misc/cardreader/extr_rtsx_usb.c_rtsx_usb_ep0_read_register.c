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
typedef  int u16 ;
struct rtsx_ucr {int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EP0_OP_SHIFT ; 
 int EP0_READ_REG_CMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTSX_USB_REQ_REG_OP ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int swab16 (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtsx_usb_ep0_read_register(struct rtsx_ucr *ucr, u16 addr, u8 *data)
{
	u16 value;
	u8 *buf;
	int ret;

	if (!data)
		return -EINVAL;

	buf = kzalloc(sizeof(u8), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	addr |= EP0_READ_REG_CMD << EP0_OP_SHIFT;
	value = swab16(addr);

	ret = usb_control_msg(ucr->pusb_dev,
			usb_rcvctrlpipe(ucr->pusb_dev, 0), RTSX_USB_REQ_REG_OP,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, 0, buf, 1, 100);
	*data = *buf;

	kfree(buf);
	return ret;
}