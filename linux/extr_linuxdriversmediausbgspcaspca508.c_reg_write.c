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
struct usb_device {int dummy; } ;
struct gspca_dev {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_write(struct gspca_dev *gspca_dev, u16 index, u16 value)
{
	int ret;
	struct usb_device *dev = gspca_dev->dev;

	ret = usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,		/* request */
			USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, NULL, 0, 500);
	gspca_dbg(gspca_dev, D_USBO, "reg write i:0x%04x = 0x%02x\n",
		  index, value);
	if (ret < 0)
		pr_err("reg write: error %d\n", ret);
	return ret;
}