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
struct gspca_dev {int usb_err; int /*<<< orphan*/  usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_wb(struct gspca_dev *gspca_dev, u16 value, u16 index,
		const u8 *data, int len)
{
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	gspca_dbg(gspca_dev, D_USBO, "reg_wb v: %04x i: %04x %02x...%02x\n",
		  value, index, *data, data[len - 1]);
	memcpy(gspca_dev->usb_buf, data, len);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x0c,			/* request */
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, gspca_dev->usb_buf, len,
			1000);
	msleep(30);
	if (ret < 0) {
		pr_err("reg_wb %04x %04x failed %d\n", value, index, ret);
		gspca_dev->usb_err = ret;
	}
}