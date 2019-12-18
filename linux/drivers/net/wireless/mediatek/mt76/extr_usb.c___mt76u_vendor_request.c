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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 int MT_VEND_REQ_MAX_RETRY ; 
 int /*<<< orphan*/  MT_VEND_REQ_TOUT_MS ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_device* to_usb_device (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __mt76u_vendor_request(struct mt76_dev *dev, u8 req,
				  u8 req_type, u16 val, u16 offset,
				  void *buf, size_t len)
{
	struct usb_device *udev = to_usb_device(dev->dev);
	unsigned int pipe;
	int i, ret;

	pipe = (req_type & USB_DIR_IN) ? usb_rcvctrlpipe(udev, 0)
				       : usb_sndctrlpipe(udev, 0);
	for (i = 0; i < MT_VEND_REQ_MAX_RETRY; i++) {
		if (test_bit(MT76_REMOVED, &dev->state))
			return -EIO;

		ret = usb_control_msg(udev, pipe, req, req_type, val,
				      offset, buf, len, MT_VEND_REQ_TOUT_MS);
		if (ret == -ENODEV)
			set_bit(MT76_REMOVED, &dev->state);
		if (ret >= 0 || ret == -ENODEV)
			return ret;
		usleep_range(5000, 10000);
	}

	dev_err(dev->dev, "vendor request req:%02x off:%04x failed:%d\n",
		req, offset, ret);
	return ret;
}