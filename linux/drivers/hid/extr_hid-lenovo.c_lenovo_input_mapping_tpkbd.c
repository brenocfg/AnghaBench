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
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HID_UP_BUTTON ; 
 int /*<<< orphan*/  KEY_MICMUTE ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,void*) ; 
 int /*<<< orphan*/  map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_input_mapping_tpkbd(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	if (usage->hid == (HID_UP_BUTTON | 0x0010)) {
		/* This sub-device contains trackpoint, mark it */
		hid_set_drvdata(hdev, (void *)1);
		map_key_clear(KEY_MICMUTE);
		return 1;
	}
	return 0;
}