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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * usb_buf; struct usb_device* dev; } ;
struct sd {TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  STV06XX_URB_MSG_TIMEOUT ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int stv06xx_read_bridge(struct sd *sd, u16 address, u8 *i2c_data)
{
	int err;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	struct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	err = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      0x04, 0xc0, address, 0, buf, 1,
			      STV06XX_URB_MSG_TIMEOUT);

	*i2c_data = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "Reading 0x%x from address 0x%x, status %d\n",
		  *i2c_data, address, err);

	return (err < 0) ? err : 0;
}