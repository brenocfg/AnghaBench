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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int usb_err; scalar_t__ usb_buf; int /*<<< orphan*/  dev; } ;
struct sd {TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov518_reg_w32(struct sd *sd, u16 index, u32 value, int n)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int ret;

	if (sd->gspca_dev.usb_err < 0)
		return;

	*((__le32 *) sd->gspca_dev.usb_buf) = __cpu_to_le32(value);

	/* Avoid things going to fast for the bridge with a xhci host */
	udelay(150);
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			1 /* REG_IO */,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			sd->gspca_dev.usb_buf, n, 500);
	if (ret < 0) {
		gspca_err(gspca_dev, "reg_w32 %02x failed %d\n", index, ret);
		sd->gspca_dev.usb_err = ret;
	}
}