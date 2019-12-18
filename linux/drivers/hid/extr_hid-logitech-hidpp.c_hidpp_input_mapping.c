#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hidpp_device {int quirks; } ;
struct hid_usage {int dummy; } ;
struct hid_input {int dummy; } ;
struct hid_field {scalar_t__ application; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HIDPP_QUIRK_CLASS_M560 ; 
 int HIDPP_QUIRK_CLASS_WTP ; 
 scalar_t__ HID_GD_MOUSE ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int m560_input_mapping (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 
 int wtp_input_mapping (struct hid_device*,struct hid_input*,struct hid_field*,struct hid_usage*,unsigned long**,int*) ; 

__attribute__((used)) static int hidpp_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);

	if (!hidpp)
		return 0;

	if (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)
		return wtp_input_mapping(hdev, hi, field, usage, bit, max);
	else if (hidpp->quirks & HIDPP_QUIRK_CLASS_M560 &&
			field->application != HID_GD_MOUSE)
		return m560_input_mapping(hdev, hi, field, usage, bit, max);

	return 0;
}