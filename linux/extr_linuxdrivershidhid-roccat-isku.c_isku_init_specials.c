#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device {int dummy; } ;
struct isku_roccat_report {int dummy; } ;
struct isku_device {int chrdev_minor; int roccat_claimed; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_3__ dev; } ;
struct TYPE_4__ {scalar_t__ bInterfaceProtocol; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ISKU_USB_INTERFACE_PROTOCOL ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct isku_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  isku_class ; 
 int isku_init_isku_device_struct (struct usb_device*,struct isku_device*) ; 
 int /*<<< orphan*/  kfree (struct isku_device*) ; 
 struct isku_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int roccat_connect (int /*<<< orphan*/ ,struct hid_device*,int) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isku_init_specials(struct hid_device *hdev)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct isku_device *isku;
	int retval;

	if (intf->cur_altsetting->desc.bInterfaceProtocol
			!= ISKU_USB_INTERFACE_PROTOCOL) {
		hid_set_drvdata(hdev, NULL);
		return 0;
	}

	isku = kzalloc(sizeof(*isku), GFP_KERNEL);
	if (!isku) {
		hid_err(hdev, "can't alloc device descriptor\n");
		return -ENOMEM;
	}
	hid_set_drvdata(hdev, isku);

	retval = isku_init_isku_device_struct(usb_dev, isku);
	if (retval) {
		hid_err(hdev, "couldn't init struct isku_device\n");
		goto exit_free;
	}

	retval = roccat_connect(isku_class, hdev,
			sizeof(struct isku_roccat_report));
	if (retval < 0) {
		hid_err(hdev, "couldn't init char dev\n");
	} else {
		isku->chrdev_minor = retval;
		isku->roccat_claimed = 1;
	}

	return 0;
exit_free:
	kfree(isku);
	return retval;
}