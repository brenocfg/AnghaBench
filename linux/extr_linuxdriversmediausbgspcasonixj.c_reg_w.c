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
 int USB_BUF_SZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev,
			  u16 value,
			  const u8 *buffer,
			  int len)
{
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	gspca_dbg(gspca_dev, D_USBO, "reg_w [%04x] = %02x %02x ..\n",
		  value, buffer[0], buffer[1]);

	if (len > USB_BUF_SZ) {
		gspca_err(gspca_dev, "reg_w: buffer overflow\n");
		return;
	}

	memcpy(gspca_dev->usb_buf, buffer, len);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x08,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			value, 0,
			gspca_dev->usb_buf, len,
			500);
	if (ret < 0) {
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}