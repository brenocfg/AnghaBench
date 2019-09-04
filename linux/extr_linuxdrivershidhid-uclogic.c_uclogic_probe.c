#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_4__* cur_altsetting; } ;
struct usb_device {TYPE_2__* config; } ;
struct uclogic_drvdata {int invert_pen_inrange; int has_virtual_pad_interface; int ignore_pen_usage; } ;
struct hid_device_id {int product; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_5__ dev; int /*<<< orphan*/  quirks; } ;
struct TYPE_8__ {int bInterfaceNumber; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;
struct TYPE_6__ {int bNumInterfaces; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_QUIRK_MULTI_INPUT ; 
#define  USB_DEVICE_ID_HUION_TABLET 135 
#define  USB_DEVICE_ID_UCLOGIC_DRAWIMAGE_G3 134 
#define  USB_DEVICE_ID_UCLOGIC_TABLET_TWHA60 133 
#define  USB_DEVICE_ID_UGEE_TABLET_45 132 
#define  USB_DEVICE_ID_UGEE_TABLET_81 131 
#define  USB_DEVICE_ID_UGEE_TABLET_EX07S 130 
#define  USB_DEVICE_ID_UGTIZER_TABLET_GP0610 129 
#define  USB_DEVICE_ID_YIYNOVA_TABLET 128 
 struct uclogic_drvdata* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct uclogic_drvdata*) ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int uclogic_button_enable (struct hid_device*) ; 
 int uclogic_tablet_enable (struct hid_device*) ; 

__attribute__((used)) static int uclogic_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	int rc;
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct usb_device *udev = hid_to_usb_dev(hdev);
	struct uclogic_drvdata *drvdata;

	/*
	 * libinput requires the pad interface to be on a different node
	 * than the pen, so use QUIRK_MULTI_INPUT for all tablets.
	 */
	hdev->quirks |= HID_QUIRK_MULTI_INPUT;

	/* Allocate and assign driver data */
	drvdata = devm_kzalloc(&hdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	hid_set_drvdata(hdev, drvdata);

	switch (id->product) {
	case USB_DEVICE_ID_HUION_TABLET:
	case USB_DEVICE_ID_YIYNOVA_TABLET:
	case USB_DEVICE_ID_UGEE_TABLET_81:
	case USB_DEVICE_ID_UCLOGIC_DRAWIMAGE_G3:
	case USB_DEVICE_ID_UGEE_TABLET_45:
		/* If this is the pen interface */
		if (intf->cur_altsetting->desc.bInterfaceNumber == 0) {
			rc = uclogic_tablet_enable(hdev);
			if (rc) {
				hid_err(hdev, "tablet enabling failed\n");
				return rc;
			}
			drvdata->invert_pen_inrange = true;

			rc = uclogic_button_enable(hdev);
			drvdata->has_virtual_pad_interface = !rc;
		} else {
			drvdata->ignore_pen_usage = true;
		}
		break;
	case USB_DEVICE_ID_UGTIZER_TABLET_GP0610:
	case USB_DEVICE_ID_UGEE_TABLET_EX07S:
		/* If this is the pen interface */
		if (intf->cur_altsetting->desc.bInterfaceNumber == 1) {
			rc = uclogic_tablet_enable(hdev);
			if (rc) {
				hid_err(hdev, "tablet enabling failed\n");
				return rc;
			}
			drvdata->invert_pen_inrange = true;
		} else {
			drvdata->ignore_pen_usage = true;
		}
		break;
	case USB_DEVICE_ID_UCLOGIC_TABLET_TWHA60:
		/*
		 * If it is the three-interface version, which is known to
		 * respond to initialization.
		 */
		if (udev->config->desc.bNumInterfaces == 3) {
			/* If it is the pen interface */
			if (intf->cur_altsetting->desc.bInterfaceNumber == 0) {
				rc = uclogic_tablet_enable(hdev);
				if (rc) {
					hid_err(hdev, "tablet enabling failed\n");
					return rc;
				}
				drvdata->invert_pen_inrange = true;

				rc = uclogic_button_enable(hdev);
				drvdata->has_virtual_pad_interface = !rc;
			} else {
				drvdata->ignore_pen_usage = true;
			}
		}
		break;
	}

	rc = hid_parse(hdev);
	if (rc) {
		hid_err(hdev, "parse failed\n");
		return rc;
	}

	rc = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (rc) {
		hid_err(hdev, "hw start failed\n");
		return rc;
	}

	return 0;
}