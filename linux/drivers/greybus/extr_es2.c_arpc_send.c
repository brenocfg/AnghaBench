#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int /*<<< orphan*/  dev; } ;
struct es2_ap_dev {struct usb_device* usb_dev; } ;
struct arpc {TYPE_1__* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ES2_USB_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  GB_APB_REQUEST_ARPC_RUN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arpc_send(struct es2_ap_dev *es2, struct arpc *rpc, int timeout)
{
	struct usb_device *udev = es2->usb_dev;
	int retval;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 GB_APB_REQUEST_ARPC_RUN,
				 USB_DIR_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE,
				 0, 0,
				 rpc->req, le16_to_cpu(rpc->req->size),
				 ES2_USB_CTRL_TIMEOUT);
	if (retval != le16_to_cpu(rpc->req->size)) {
		dev_err(&udev->dev,
			"failed to send ARPC request %d: %d\n",
			rpc->req->type, retval);
		if (retval > 0)
			retval = -EIO;
		return retval;
	}

	return 0;
}