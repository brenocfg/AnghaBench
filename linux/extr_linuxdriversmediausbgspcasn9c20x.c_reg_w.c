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
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev, u16 reg,
		 const u8 *buffer, int length)
{
	struct usb_device *dev = gspca_dev->dev;
	int result;

	if (gspca_dev->usb_err < 0)
		return;
	memcpy(gspca_dev->usb_buf, buffer, length);
	result = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			0x08,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			reg,
			0x00,
			gspca_dev->usb_buf,
			length,
			500);
	if (unlikely(result < 0 || result != length)) {
		pr_err("Write register %02x failed %d\n", reg, result);
		gspca_dev->usb_err = result;
	}
}