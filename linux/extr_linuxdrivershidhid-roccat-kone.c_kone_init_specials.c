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
struct kone_roccat_report {int dummy; } ;
struct kone_device {int roccat_claimed; int chrdev_minor; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_3__ dev; } ;
struct TYPE_4__ {scalar_t__ bInterfaceProtocol; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_INTERFACE_PROTOCOL_MOUSE ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct kone_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct kone_device*) ; 
 int /*<<< orphan*/  kone_class ; 
 int kone_init_kone_device_struct (struct usb_device*,struct kone_device*) ; 
 struct kone_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int roccat_connect (int /*<<< orphan*/ ,struct hid_device*,int) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kone_init_specials(struct hid_device *hdev)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct kone_device *kone;
	int retval;

	if (intf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) {

		kone = kzalloc(sizeof(*kone), GFP_KERNEL);
		if (!kone)
			return -ENOMEM;
		hid_set_drvdata(hdev, kone);

		retval = kone_init_kone_device_struct(usb_dev, kone);
		if (retval) {
			hid_err(hdev, "couldn't init struct kone_device\n");
			goto exit_free;
		}

		retval = roccat_connect(kone_class, hdev,
				sizeof(struct kone_roccat_report));
		if (retval < 0) {
			hid_err(hdev, "couldn't init char dev\n");
			/* be tolerant about not getting chrdev */
		} else {
			kone->roccat_claimed = 1;
			kone->chrdev_minor = retval;
		}
	} else {
		hid_set_drvdata(hdev, NULL);
	}

	return 0;
exit_free:
	kfree(kone);
	return retval;
}