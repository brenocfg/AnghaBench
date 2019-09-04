#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  touch_max; } ;
struct wacom_wac {TYPE_1__ features; int /*<<< orphan*/  touch_input; scalar_t__ is_direct_mode; scalar_t__ has_mode_change; } ;
struct wacom_features {scalar_t__ type; int device_type; int touch_max; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HID_GENERIC ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int /*<<< orphan*/  INPUT_MT_POINTER ; 
 int WACOM_DEVICETYPE_DIRECT ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_mt_init_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_post_parse_hid(struct hid_device *hdev,
				 struct wacom_features *features)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;

	if (features->type == HID_GENERIC) {
		/* Any last-minute generic device setup */
		if (wacom_wac->has_mode_change) {
			if (wacom_wac->is_direct_mode)
				features->device_type |= WACOM_DEVICETYPE_DIRECT;
			else
				features->device_type &= ~WACOM_DEVICETYPE_DIRECT;
		}

		if (features->touch_max > 1) {
			if (features->device_type & WACOM_DEVICETYPE_DIRECT)
				input_mt_init_slots(wacom_wac->touch_input,
						    wacom_wac->features.touch_max,
						    INPUT_MT_DIRECT);
			else
				input_mt_init_slots(wacom_wac->touch_input,
						    wacom_wac->features.touch_max,
						    INPUT_MT_POINTER);
		}
	}
}