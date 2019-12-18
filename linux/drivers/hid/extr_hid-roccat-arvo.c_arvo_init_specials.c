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
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_3__ dev; } ;
struct arvo_roccat_report {int dummy; } ;
struct arvo_device {int chrdev_minor; int roccat_claimed; } ;
struct TYPE_4__ {scalar_t__ bInterfaceProtocol; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_INTERFACE_PROTOCOL_KEYBOARD ; 
 int /*<<< orphan*/  arvo_class ; 
 int arvo_init_arvo_device_struct (struct usb_device*,struct arvo_device*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct arvo_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct arvo_device*) ; 
 struct arvo_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int roccat_connect (int /*<<< orphan*/ ,struct hid_device*,int) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arvo_init_specials(struct hid_device *hdev)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct arvo_device *arvo;
	int retval;

	if (intf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_KEYBOARD) {
		hid_set_drvdata(hdev, NULL);
		return 0;
	}

	arvo = kzalloc(sizeof(*arvo), GFP_KERNEL);
	if (!arvo) {
		hid_err(hdev, "can't alloc device descriptor\n");
		return -ENOMEM;
	}
	hid_set_drvdata(hdev, arvo);

	retval = arvo_init_arvo_device_struct(usb_dev, arvo);
	if (retval) {
		hid_err(hdev, "couldn't init struct arvo_device\n");
		goto exit_free;
	}

	retval = roccat_connect(arvo_class, hdev,
			sizeof(struct arvo_roccat_report));
	if (retval < 0) {
		hid_err(hdev, "couldn't init char dev\n");
	} else {
		arvo->chrdev_minor = retval;
		arvo->roccat_claimed = 1;
	}

	return 0;
exit_free:
	kfree(arvo);
	return retval;
}