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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
#define  USB_STATUS_TYPE_PTM 129 
#define  USB_STATUS_TYPE_STANDARD 128 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int usb_get_status(struct usb_device *dev, int recip, int type, int target,
		void *data)
{
	int ret;
	void *status;
	int length;

	switch (type) {
	case USB_STATUS_TYPE_STANDARD:
		length = 2;
		break;
	case USB_STATUS_TYPE_PTM:
		if (recip != USB_RECIP_DEVICE)
			return -EINVAL;

		length = 4;
		break;
	default:
		return -EINVAL;
	}

	status =  kmalloc(length, GFP_KERNEL);
	if (!status)
		return -ENOMEM;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_STATUS, USB_DIR_IN | recip, USB_STATUS_TYPE_STANDARD,
		target, status, length, USB_CTRL_GET_TIMEOUT);

	switch (ret) {
	case 4:
		if (type != USB_STATUS_TYPE_PTM) {
			ret = -EIO;
			break;
		}

		*(u32 *) data = le32_to_cpu(*(__le32 *) status);
		ret = 0;
		break;
	case 2:
		if (type != USB_STATUS_TYPE_STANDARD) {
			ret = -EIO;
			break;
		}

		*(u16 *) data = le16_to_cpu(*(__le16 *) status);
		ret = 0;
		break;
	default:
		ret = -EIO;
	}

	kfree(status);
	return ret;
}