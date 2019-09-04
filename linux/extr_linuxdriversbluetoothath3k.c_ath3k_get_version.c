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
struct ath3k_version {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH3K_GETVERSION ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (struct ath3k_version*) ; 
 struct ath3k_version* kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ath3k_version*,struct ath3k_version*,int const) ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath3k_version*,int const,int /*<<< orphan*/ ) ; 
 int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath3k_get_version(struct usb_device *udev,
			struct ath3k_version *version)
{
	int ret, pipe = 0;
	struct ath3k_version *buf;
	const int size = sizeof(*buf);

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	pipe = usb_rcvctrlpipe(udev, 0);
	ret = usb_control_msg(udev, pipe, ATH3K_GETVERSION,
			      USB_TYPE_VENDOR | USB_DIR_IN, 0, 0,
			      buf, size, USB_CTRL_SET_TIMEOUT);

	memcpy(version, buf, size);
	kfree(buf);

	return ret;
}