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
struct redrat3_dev {struct device* dev; struct usb_device* udev; } ;
struct rc_dev {struct redrat3_dev* priv; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  RR3_IR_IO_SIG_TIMEOUT ; 
 int /*<<< orphan*/  RR3_SET_IR_PARAM ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redrat3_us_to_len (unsigned int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redrat3_set_timeout(struct rc_dev *rc_dev, unsigned int timeoutns)
{
	struct redrat3_dev *rr3 = rc_dev->priv;
	struct usb_device *udev = rr3->udev;
	struct device *dev = rr3->dev;
	__be32 *timeout;
	int ret;

	timeout = kmalloc(sizeof(*timeout), GFP_KERNEL);
	if (!timeout)
		return -ENOMEM;

	*timeout = cpu_to_be32(redrat3_us_to_len(timeoutns / 1000));
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), RR3_SET_IR_PARAM,
		     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT,
		     RR3_IR_IO_SIG_TIMEOUT, 0, timeout, sizeof(*timeout),
		     HZ * 25);
	dev_dbg(dev, "set ir parm timeout %d ret 0x%02x\n",
						be32_to_cpu(*timeout), ret);

	if (ret == sizeof(*timeout))
		ret = 0;
	else if (ret >= 0)
		ret = -EIO;

	kfree(timeout);

	return ret;
}