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
struct hid_device_id {unsigned long driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_3__ dev; } ;
struct corsair_drvdata {unsigned long quirks; } ;
struct TYPE_4__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 unsigned long CORSAIR_USE_K90_BACKLIGHT ; 
 unsigned long CORSAIR_USE_K90_MACRO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 struct corsair_drvdata* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct corsair_drvdata*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*) ; 
 int k90_init_backlight (struct hid_device*) ; 
 int k90_init_macro_functions (struct hid_device*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int corsair_probe(struct hid_device *dev, const struct hid_device_id *id)
{
	int ret;
	unsigned long quirks = id->driver_data;
	struct corsair_drvdata *drvdata;
	struct usb_interface *usbif = to_usb_interface(dev->dev.parent);

	drvdata = devm_kzalloc(&dev->dev, sizeof(struct corsair_drvdata),
			       GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;
	drvdata->quirks = quirks;
	hid_set_drvdata(dev, drvdata);

	ret = hid_parse(dev);
	if (ret != 0) {
		hid_err(dev, "parse failed\n");
		return ret;
	}
	ret = hid_hw_start(dev, HID_CONNECT_DEFAULT);
	if (ret != 0) {
		hid_err(dev, "hw start failed\n");
		return ret;
	}

	if (usbif->cur_altsetting->desc.bInterfaceNumber == 0) {
		if (quirks & CORSAIR_USE_K90_MACRO) {
			ret = k90_init_macro_functions(dev);
			if (ret != 0)
				hid_warn(dev, "Failed to initialize K90 macro functions.\n");
		}
		if (quirks & CORSAIR_USE_K90_BACKLIGHT) {
			ret = k90_init_backlight(dev);
			if (ret != 0)
				hid_warn(dev, "Failed to initialize K90 backlight.\n");
		}
	}

	return 0;
}