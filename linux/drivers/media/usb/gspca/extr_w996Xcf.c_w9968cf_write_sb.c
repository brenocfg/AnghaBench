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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int usb_err; int /*<<< orphan*/  dev; } ;
struct sd {TYPE_1__ gspca_dev; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int W9968CF_I2C_BUS_DELAY ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w9968cf_write_sb(struct sd *sd, u16 value)
{
	int ret;

	if (sd->gspca_dev.usb_err < 0)
		return;

	/* Avoid things going to fast for the bridge with a xhci host */
	udelay(150);

	/* We don't use reg_w here, as that would cause all writes when
	   bitbanging i2c to be logged, making the logs impossible to read */
	ret = usb_control_msg(sd->gspca_dev.dev,
		usb_sndctrlpipe(sd->gspca_dev.dev, 0),
		0,
		USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		value, 0x01, NULL, 0, 500);

	udelay(W9968CF_I2C_BUS_DELAY);

	if (ret < 0) {
		pr_err("Write SB reg [01] %04x failed\n", value);
		sd->gspca_dev.usb_err = ret;
	}
}