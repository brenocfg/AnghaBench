#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int inputmode; } ;
struct wacom_features {scalar_t__ hid_type; scalar_t__ check_for_hid_type; } ;
struct wacom_wac {int mode_report; TYPE_1__ hid_data; int /*<<< orphan*/  pen_fifo; struct wacom_features features; } ;
struct wacom {int /*<<< orphan*/  mode_change_work; int /*<<< orphan*/  remote_work; int /*<<< orphan*/  battery_work; int /*<<< orphan*/  wireless_work; int /*<<< orphan*/  init_work; int /*<<< orphan*/  lock; struct usb_interface* intf; struct usb_device* usbdev; struct wacom_wac wacom_wac; struct hid_device* hdev; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct hid_device_id {scalar_t__ driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct hid_device {scalar_t__ type; scalar_t__ bus; TYPE_2__ dev; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 scalar_t__ BUS_BLUETOOTH ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_QUIRK_NOGET ; 
 int /*<<< orphan*/  HID_QUIRK_NO_INIT_REPORTS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WACOM_PKGLEN_MAX ; 
 int /*<<< orphan*/  dev_attr_speed ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct wacom* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct wacom*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_battery_work ; 
 int /*<<< orphan*/  wacom_init_work ; 
 int /*<<< orphan*/  wacom_mode_change_work ; 
 int wacom_parse_and_register (struct wacom*,int) ; 
 int /*<<< orphan*/  wacom_remote_work ; 
 int /*<<< orphan*/  wacom_wireless_work ; 

__attribute__((used)) static int wacom_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct usb_device *dev = interface_to_usbdev(intf);
	struct wacom *wacom;
	struct wacom_wac *wacom_wac;
	struct wacom_features *features;
	int error;

	if (!id->driver_data)
		return -EINVAL;

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	/* hid-core sets this quirk for the boot interface */
	hdev->quirks &= ~HID_QUIRK_NOGET;

	wacom = devm_kzalloc(&hdev->dev, sizeof(struct wacom), GFP_KERNEL);
	if (!wacom)
		return -ENOMEM;

	hid_set_drvdata(hdev, wacom);
	wacom->hdev = hdev;

	wacom_wac = &wacom->wacom_wac;
	wacom_wac->features = *((struct wacom_features *)id->driver_data);
	features = &wacom_wac->features;

	if (features->check_for_hid_type && features->hid_type != hdev->type)
		return -ENODEV;

	error = kfifo_alloc(&wacom_wac->pen_fifo, WACOM_PKGLEN_MAX, GFP_KERNEL);
	if (error)
		return error;

	wacom_wac->hid_data.inputmode = -1;
	wacom_wac->mode_report = -1;

	wacom->usbdev = dev;
	wacom->intf = intf;
	mutex_init(&wacom->lock);
	INIT_DELAYED_WORK(&wacom->init_work, wacom_init_work);
	INIT_WORK(&wacom->wireless_work, wacom_wireless_work);
	INIT_WORK(&wacom->battery_work, wacom_battery_work);
	INIT_WORK(&wacom->remote_work, wacom_remote_work);
	INIT_WORK(&wacom->mode_change_work, wacom_mode_change_work);

	/* ask for the report descriptor to be loaded by HID */
	error = hid_parse(hdev);
	if (error) {
		hid_err(hdev, "parse failed\n");
		return error;
	}

	error = wacom_parse_and_register(wacom, false);
	if (error)
		return error;

	if (hdev->bus == BUS_BLUETOOTH) {
		error = device_create_file(&hdev->dev, &dev_attr_speed);
		if (error)
			hid_warn(hdev,
				 "can't create sysfs speed attribute err: %d\n",
				 error);
	}

	return 0;
}