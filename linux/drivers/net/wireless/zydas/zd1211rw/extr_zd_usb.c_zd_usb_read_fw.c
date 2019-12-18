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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct zd_usb {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  USB_REQ_FIRMWARE_READ_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

int zd_usb_read_fw(struct zd_usb *usb, zd_addr_t addr, u8 *data, u16 len)
{
	int r;
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	u8 *buf;

	/* Use "DMA-aware" buffer. */
	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
		USB_REQ_FIRMWARE_READ_DATA, USB_DIR_IN | 0x40, addr, 0,
		buf, len, 5000);
	if (r < 0) {
		dev_err(&udev->dev,
			"read over firmware interface failed: %d\n", r);
		goto exit;
	} else if (r != len) {
		dev_err(&udev->dev,
			"incomplete read over firmware interface: %d/%d\n",
			r, len);
		r = -EIO;
		goto exit;
	}
	r = 0;
	memcpy(data, buf, len);
exit:
	kfree(buf);
	return r;
}