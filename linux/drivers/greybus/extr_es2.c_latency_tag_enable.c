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
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct gb_host_device {int dummy; } ;
struct es2_ap_dev {struct usb_device* usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES2_USB_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  GB_APB_REQUEST_LATENCY_TAG_EN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct es2_ap_dev* hd_to_es2 (struct gb_host_device*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int latency_tag_enable(struct gb_host_device *hd, u16 cport_id)
{
	int retval;
	struct es2_ap_dev *es2 = hd_to_es2(hd);
	struct usb_device *udev = es2->usb_dev;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 GB_APB_REQUEST_LATENCY_TAG_EN,
				 USB_DIR_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE, cport_id, 0, NULL,
				 0, ES2_USB_CTRL_TIMEOUT);

	if (retval < 0)
		dev_err(&udev->dev, "Cannot enable latency tag for cport %d\n",
			cport_id);
	return retval;
}