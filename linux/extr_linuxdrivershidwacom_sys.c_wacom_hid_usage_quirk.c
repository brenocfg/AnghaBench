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
struct wacom_features {scalar_t__ type; } ;
struct TYPE_5__ {int mode_value; int /*<<< orphan*/  mode_report; struct wacom_features features; } ;
struct wacom {TYPE_2__ wacom_wac; } ;
struct hid_usage {int hid; int usage_index; } ;
struct hid_field {scalar_t__ application; scalar_t__ physical; int maxusage; int logical_maximum; TYPE_3__* usage; TYPE_1__* report; } ;
struct hid_device {scalar_t__ vendor; int product; } ;
struct TYPE_6__ {scalar_t__ hid; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ HID_DG_BARRELSWITCH ; 
 int HID_DG_BARRELSWITCH2 ; 
 scalar_t__ HID_DG_ERASER ; 
 scalar_t__ HID_DG_INRANGE ; 
 scalar_t__ HID_DG_INVERT ; 
 scalar_t__ HID_DG_PEN ; 
 scalar_t__ HID_DG_STYLUS ; 
 scalar_t__ HID_DG_TIPSWITCH ; 
 unsigned int HID_GD_Y ; 
 scalar_t__ HID_GENERIC ; 
 scalar_t__ HID_UP_MSVENDOR ; 
 scalar_t__ USB_VENDOR_ID_WACOM ; 
 scalar_t__ WACOM_PEN_FIELD (struct hid_field*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int) ; 

__attribute__((used)) static void wacom_hid_usage_quirk(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_features *features = &wacom->wacom_wac.features;
	unsigned int equivalent_usage = wacom_equivalent_usage(usage->hid);

	/*
	 * The Dell Canvas 27 needs to be switched to its vendor-defined
	 * report to provide the best resolution.
	 */
	if (hdev->vendor == USB_VENDOR_ID_WACOM &&
	    hdev->product == 0x4200 &&
	    field->application == HID_UP_MSVENDOR) {
		wacom->wacom_wac.mode_report = field->report->id;
		wacom->wacom_wac.mode_value = 2;
	}

	/*
	 * ISDv4 devices which predate HID's adoption of the
	 * HID_DG_BARELSWITCH2 usage use 0x000D0000 in its
	 * position instead. We can accurately detect if a
	 * usage with that value should be HID_DG_BARRELSWITCH2
	 * based on the surrounding usages, which have remained
	 * constant across generations.
	 */
	if (features->type == HID_GENERIC &&
	    usage->hid == 0x000D0000 &&
	    field->application == HID_DG_PEN &&
	    field->physical == HID_DG_STYLUS) {
		int i = usage->usage_index;

		if (i-4 >= 0 && i+1 < field->maxusage &&
		    field->usage[i-4].hid == HID_DG_TIPSWITCH &&
		    field->usage[i-3].hid == HID_DG_BARRELSWITCH &&
		    field->usage[i-2].hid == HID_DG_ERASER &&
		    field->usage[i-1].hid == HID_DG_INVERT &&
		    field->usage[i+1].hid == HID_DG_INRANGE) {
			usage->hid = HID_DG_BARRELSWITCH2;
		}
	}

	/* 2nd-generation Intuos Pro Large has incorrect Y maximum */
	if (hdev->vendor == USB_VENDOR_ID_WACOM &&
	    hdev->product == 0x0358 &&
	    WACOM_PEN_FIELD(field) &&
	    equivalent_usage == HID_GD_Y) {
		field->logical_maximum = 43200;
	}
}