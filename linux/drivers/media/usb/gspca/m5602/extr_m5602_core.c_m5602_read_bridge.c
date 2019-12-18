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
typedef  scalar_t__ u8 ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {scalar_t__* usb_buf; struct usb_device* dev; } ;
struct sd {TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  M5602_URB_MSG_TIMEOUT ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__ const,scalar_t__) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,scalar_t__ const,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int m5602_read_bridge(struct sd *sd, const u8 address, u8 *i2c_data)
{
	int err;
	struct gspca_dev *gspca_dev = (struct gspca_dev *) sd;
	struct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	err = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      0x04, 0xc0, 0x14,
			      0x8100 + address, buf,
			      1, M5602_URB_MSG_TIMEOUT);
	*i2c_data = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "Reading bridge register 0x%x containing 0x%x\n",
		  address, *i2c_data);

	/* usb_control_msg(...) returns the number of bytes sent upon success,
	mask that and return zero instead*/
	return (err < 0) ? err : 0;
}