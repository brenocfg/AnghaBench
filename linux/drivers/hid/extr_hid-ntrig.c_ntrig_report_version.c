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
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_CLEAR_FEATURE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*,char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int ntrig_version_string (unsigned char*,char*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntrig_report_version(struct hid_device *hdev)
{
	int ret;
	char buf[20];
	struct usb_device *usb_dev = hid_to_usb_dev(hdev);
	unsigned char *data = kmalloc(8, GFP_KERNEL);

	if (!data)
		goto err_free;

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      USB_REQ_CLEAR_FEATURE,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE |
			      USB_DIR_IN,
			      0x30c, 1, data, 8,
			      USB_CTRL_SET_TIMEOUT);

	if (ret == 8) {
		ret = ntrig_version_string(&data[2], buf);

		hid_info(hdev, "Firmware version: %s (%02x%02x %02x%02x)\n",
			 buf, data[2], data[3], data[4], data[5]);
	}

err_free:
	kfree(data);
}