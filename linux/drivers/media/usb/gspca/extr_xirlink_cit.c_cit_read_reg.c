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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; struct usb_device* dev; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int USB_DIR_IN ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cit_read_reg(struct gspca_dev *gspca_dev, u16 index, int verbose)
{
	struct usb_device *udev = gspca_dev->dev;
	__u8 *buf = gspca_dev->usb_buf;
	int res;

	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x01,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT,
			0x00, index, buf, 8, 1000);
	if (res < 0) {
		pr_err("Failed to read a register (index 0x%04X, error %d)\n",
		       index, res);
		return res;
	}

	if (verbose)
		gspca_dbg(gspca_dev, D_PROBE, "Register %04x value: %02x\n",
			  index, buf[0]);

	return 0;
}