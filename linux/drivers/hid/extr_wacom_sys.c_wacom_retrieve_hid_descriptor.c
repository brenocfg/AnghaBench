#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wacom_features {int x_fuzz; int y_fuzz; int distance_fuzz; int tilt_fuzz; scalar_t__ type; int /*<<< orphan*/  device_type; scalar_t__ pressure_fuzz; } ;
struct wacom {struct usb_interface* intf; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct hid_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WACOM_DEVICETYPE_NONE ; 
 int /*<<< orphan*/  WACOM_DEVICETYPE_WL_MONITOR ; 
 scalar_t__ WIRELESS ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_parse_hid (struct hid_device*,struct wacom_features*) ; 

__attribute__((used)) static void wacom_retrieve_hid_descriptor(struct hid_device *hdev,
					 struct wacom_features *features)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct usb_interface *intf = wacom->intf;

	/* default features */
	features->x_fuzz = 4;
	features->y_fuzz = 4;
	features->pressure_fuzz = 0;
	features->distance_fuzz = 1;
	features->tilt_fuzz = 1;

	/*
	 * The wireless device HID is basic and layout conflicts with
	 * other tablets (monitor and touch interface can look like pen).
	 * Skip the query for this type and modify defaults based on
	 * interface number.
	 */
	if (features->type == WIRELESS) {
		if (intf->cur_altsetting->desc.bInterfaceNumber == 0)
			features->device_type = WACOM_DEVICETYPE_WL_MONITOR;
		else
			features->device_type = WACOM_DEVICETYPE_NONE;
		return;
	}

	wacom_parse_hid(hdev, features);
}