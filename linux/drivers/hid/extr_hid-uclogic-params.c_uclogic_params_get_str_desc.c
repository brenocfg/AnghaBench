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
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int USB_DT_STRING ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,scalar_t__,int) ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uclogic_params_get_str_desc(__u8 **pbuf, struct hid_device *hdev,
					__u8 idx, size_t len)
{
	int rc;
	struct usb_device *udev = hid_to_usb_dev(hdev);
	__u8 *buf = NULL;

	/* Check arguments */
	if (hdev == NULL) {
		rc = -EINVAL;
		goto cleanup;
	}

	buf = kmalloc(len, GFP_KERNEL);
	if (buf == NULL) {
		rc = -ENOMEM;
		goto cleanup;
	}

	rc = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
				(USB_DT_STRING << 8) + idx,
				0x0409, buf, len,
				USB_CTRL_GET_TIMEOUT);
	if (rc == -EPIPE) {
		hid_dbg(hdev, "string descriptor #%hhu not found\n", idx);
		goto cleanup;
	} else if (rc < 0) {
		hid_err(hdev,
			"failed retrieving string descriptor #%hhu: %d\n",
			idx, rc);
		goto cleanup;
	}

	if (pbuf != NULL) {
		*pbuf = buf;
		buf = NULL;
	}

cleanup:
	kfree(buf);
	return rc;
}