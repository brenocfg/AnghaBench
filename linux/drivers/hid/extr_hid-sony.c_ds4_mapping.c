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
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 unsigned int HID_GD_HATSWITCH ; 
 int HID_UP_BUTTON ; 
 int HID_UP_GENDESK ; 
 unsigned int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 unsigned int* ds4_absmap ; 
 unsigned int* ds4_keymap ; 
 int /*<<< orphan*/  hid_map_usage_clear (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ds4_mapping(struct hid_device *hdev, struct hid_input *hi,
		       struct hid_field *field, struct hid_usage *usage,
		       unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		unsigned int key = usage->hid & HID_USAGE;

		if (key >= ARRAY_SIZE(ds4_keymap))
			return -1;

		key = ds4_keymap[key];
		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		return 1;
	} else if ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) {
		unsigned int abs = usage->hid & HID_USAGE;

		/* Let the HID parser deal with the HAT. */
		if (usage->hid == HID_GD_HATSWITCH)
			return 0;

		if (abs >= ARRAY_SIZE(ds4_absmap))
			return -1;

		abs = ds4_absmap[abs];
		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, abs);
		return 1;
	}

	return 0;
}