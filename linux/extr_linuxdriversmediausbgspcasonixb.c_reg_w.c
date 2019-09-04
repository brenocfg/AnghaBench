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
struct gspca_dev {int usb_err; TYPE_1__ v4l2_dev; int /*<<< orphan*/  usb_buf; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev,
		  __u16 value,
		  const __u8 *buffer,
		  int len)
{
	int res;

	if (gspca_dev->usb_err < 0)
		return;

	memcpy(gspca_dev->usb_buf, buffer, len);
	res = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x08,			/* request */
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			value,
			0,			/* index */
			gspca_dev->usb_buf, len,
			500);

	if (res < 0) {
		dev_err(gspca_dev->v4l2_dev.dev,
			"Error writing register %02x: %d\n", value, res);
		gspca_dev->usb_err = res;
	}
}