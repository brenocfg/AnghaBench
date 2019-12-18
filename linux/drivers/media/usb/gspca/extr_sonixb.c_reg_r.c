#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct gspca_dev {int usb_err; scalar_t__* usb_buf; TYPE_1__ v4l2_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_r(struct gspca_dev *gspca_dev,
		  __u16 value)
{
	int res;

	if (gspca_dev->usb_err < 0)
		return;

	res = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0,			/* request */
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			value,
			0,			/* index */
			gspca_dev->usb_buf, 1,
			500);

	if (res < 0) {
		dev_err(gspca_dev->v4l2_dev.dev,
			"Error reading register %02x: %d\n", value, res);
		gspca_dev->usb_err = res;
		/*
		 * Make sure the result is zeroed to avoid uninitialized
		 * values.
		 */
		gspca_dev->usb_buf[0] = 0;
	}
}