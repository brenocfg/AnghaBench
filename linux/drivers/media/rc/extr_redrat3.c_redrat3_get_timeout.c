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
typedef  int u32 ;
struct redrat3_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int MS_TO_US (int) ; 
 int /*<<< orphan*/  RR3_GET_IR_PARAM ; 
 int /*<<< orphan*/  RR3_IR_IO_SIG_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int redrat3_len_to_us (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 redrat3_get_timeout(struct redrat3_dev *rr3)
{
	__be32 *tmp;
	u32 timeout = MS_TO_US(150); /* a sane default, if things go haywire */
	int len, ret, pipe;

	len = sizeof(*tmp);
	tmp = kzalloc(len, GFP_KERNEL);
	if (!tmp)
		return timeout;

	pipe = usb_rcvctrlpipe(rr3->udev, 0);
	ret = usb_control_msg(rr3->udev, pipe, RR3_GET_IR_PARAM,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
			      RR3_IR_IO_SIG_TIMEOUT, 0, tmp, len, HZ * 5);
	if (ret != len)
		dev_warn(rr3->dev, "Failed to read timeout from hardware\n");
	else {
		timeout = redrat3_len_to_us(be32_to_cpup(tmp));

		dev_dbg(rr3->dev, "Got timeout of %d ms\n", timeout / 1000);
	}

	kfree(tmp);

	return timeout;
}