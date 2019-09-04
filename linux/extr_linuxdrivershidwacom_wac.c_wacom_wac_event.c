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
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ touch_input; scalar_t__ pen_input; scalar_t__ pad_input; TYPE_1__ features; } ;
struct wacom {TYPE_2__ wacom_wac; } ;
struct hid_usage {int dummy; } ;
struct hid_field {scalar_t__ logical_maximum; scalar_t__ logical_minimum; } ;
struct hid_device {int dummy; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 scalar_t__ HID_GENERIC ; 
 scalar_t__ WACOM_BATTERY_USAGE (struct hid_usage*) ; 
 scalar_t__ WACOM_FINGER_FIELD (struct hid_field*) ; 
 scalar_t__ WACOM_PAD_FIELD (struct hid_field*) ; 
 scalar_t__ WACOM_PEN_FIELD (struct hid_field*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_wac_battery_event (struct hid_device*,struct hid_field*,struct hid_usage*,scalar_t__) ; 
 int /*<<< orphan*/  wacom_wac_finger_event (struct hid_device*,struct hid_field*,struct hid_usage*,scalar_t__) ; 
 int /*<<< orphan*/  wacom_wac_pad_event (struct hid_device*,struct hid_field*,struct hid_usage*,scalar_t__) ; 
 int /*<<< orphan*/  wacom_wac_pen_event (struct hid_device*,struct hid_field*,struct hid_usage*,scalar_t__) ; 

void wacom_wac_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct wacom *wacom = hid_get_drvdata(hdev);

	if (wacom->wacom_wac.features.type != HID_GENERIC)
		return;

	if (value > field->logical_maximum || value < field->logical_minimum)
		return;

	/* usage tests must precede field tests */
	if (WACOM_BATTERY_USAGE(usage))
		wacom_wac_battery_event(hdev, field, usage, value);
	else if (WACOM_PAD_FIELD(field) && wacom->wacom_wac.pad_input)
		wacom_wac_pad_event(hdev, field, usage, value);
	else if (WACOM_PEN_FIELD(field) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_event(hdev, field, usage, value);
	else if (WACOM_FINGER_FIELD(field) && wacom->wacom_wac.touch_input)
		wacom_wac_finger_event(hdev, field, usage, value);
}