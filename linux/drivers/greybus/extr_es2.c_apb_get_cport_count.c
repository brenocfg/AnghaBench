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
struct usb_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ES2_USB_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  GB_APB_REQUEST_CPORT_COUNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int U8_MAX ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apb_get_cport_count(struct usb_device *udev)
{
	int retval;
	__le16 *cport_count;

	cport_count = kzalloc(sizeof(*cport_count), GFP_KERNEL);
	if (!cport_count)
		return -ENOMEM;

	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 GB_APB_REQUEST_CPORT_COUNT,
				 USB_DIR_IN | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE, 0, 0, cport_count,
				 sizeof(*cport_count), ES2_USB_CTRL_TIMEOUT);
	if (retval != sizeof(*cport_count)) {
		dev_err(&udev->dev, "Cannot retrieve CPort count: %d\n",
			retval);

		if (retval >= 0)
			retval = -EIO;

		goto out;
	}

	retval = le16_to_cpu(*cport_count);

	/* We need to fit a CPort ID in one byte of a message header */
	if (retval > U8_MAX) {
		retval = U8_MAX;
		dev_warn(&udev->dev, "Limiting number of CPorts to U8_MAX\n");
	}

out:
	kfree(cport_count);
	return retval;
}