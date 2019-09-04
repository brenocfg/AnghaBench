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
struct usb_device {int dummy; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/  usb_buf; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_rw(struct gspca_dev *gspca_dev,
		u8 bRequestType, u8 bRequest,
		u16 wValue, u16 wIndex, u16 wLength)
{
	struct usb_device *udev = gspca_dev->dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return;

	ret = usb_control_msg(udev,
		usb_rcvctrlpipe(udev, 0),
		bRequest,
		bRequestType,
		wValue, wIndex,
		gspca_dev->usb_buf, wLength, 500);

	if (ret < 0) {
		gspca_dev->usb_err = ret;
		pr_err("usb_control_msg error %d\n", ret);
	}

	return;
}