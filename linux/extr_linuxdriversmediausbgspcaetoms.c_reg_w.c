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
struct usb_device {int dummy; } ;
struct gspca_dev {int /*<<< orphan*/  usb_buf; struct usb_device* dev; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 scalar_t__ USB_BUF_SZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev,
		  __u16 index,
		  const __u8 *buffer,
		  __u16 len)
{
	struct usb_device *dev = gspca_dev->dev;

	if (len > USB_BUF_SZ) {
		pr_err("reg_w: buffer overflow\n");
		return;
	}
	gspca_dbg(gspca_dev, D_USBO, "reg write [%02x] = %02x..\n",
		  index, *buffer);

	memcpy(gspca_dev->usb_buf, buffer, len);
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0, index, gspca_dev->usb_buf, len, 500);
}