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
struct hid_field {int flags; int logical_minimum; int logical_maximum; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  EV_REL ; 
 int HID_GD_WHEEL ; 
 int HID_MAIN_ITEM_RELATIVE ; 
 int HID_MAIN_ITEM_VARIABLE ; 
 int HID_UP_BUTTON ; 
 int HID_UP_CONSUMER ; 
 int HID_UP_LNVENDOR ; 
 int HID_UP_MSVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSDOWN ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSUP ; 
 int /*<<< orphan*/  KEY_CONFIG ; 
 int /*<<< orphan*/  KEY_FILE ; 
 int /*<<< orphan*/  KEY_FN_ESC ; 
 int /*<<< orphan*/  KEY_MICMUTE ; 
 int /*<<< orphan*/  KEY_SCALE ; 
 int /*<<< orphan*/  KEY_SWITCHVIDEOMODE ; 
 int /*<<< orphan*/  KEY_WLAN ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_input_mapping_cptkbd(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	/* HID_UP_LNVENDOR = USB, HID_UP_MSVENDOR = BT */
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOR ||
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_LNVENDOR) {
		switch (usage->hid & HID_USAGE) {
		case 0x00f1: /* Fn-F4: Mic mute */
			map_key_clear(KEY_MICMUTE);
			return 1;
		case 0x00f2: /* Fn-F5: Brightness down */
			map_key_clear(KEY_BRIGHTNESSDOWN);
			return 1;
		case 0x00f3: /* Fn-F6: Brightness up */
			map_key_clear(KEY_BRIGHTNESSUP);
			return 1;
		case 0x00f4: /* Fn-F7: External display (projector) */
			map_key_clear(KEY_SWITCHVIDEOMODE);
			return 1;
		case 0x00f5: /* Fn-F8: Wireless */
			map_key_clear(KEY_WLAN);
			return 1;
		case 0x00f6: /* Fn-F9: Control panel */
			map_key_clear(KEY_CONFIG);
			return 1;
		case 0x00f8: /* Fn-F11: View open applications (3 boxes) */
			map_key_clear(KEY_SCALE);
			return 1;
		case 0x00f9: /* Fn-F12: Open My computer (6 boxes) USB-only */
			/* NB: This mapping is invented in raw_event below */
			map_key_clear(KEY_FILE);
			return 1;
		case 0x00fa: /* Fn-Esc: Fn-lock toggle */
			map_key_clear(KEY_FN_ESC);
			return 1;
		case 0x00fb: /* Middle mouse button (in native mode) */
			map_key_clear(BTN_MIDDLE);
			return 1;
		}
	}

	/* Compatibility middle/wheel mappings should be ignored */
	if (usage->hid == HID_GD_WHEEL)
		return -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON &&
			(usage->hid & HID_USAGE) == 0x003)
		return -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER &&
			(usage->hid & HID_USAGE) == 0x238)
		return -1;

	/* Map wheel emulation reports: 0xffa1 = USB, 0xff10 = BT */
	if ((usage->hid & HID_USAGE_PAGE) == 0xff100000 ||
	    (usage->hid & HID_USAGE_PAGE) == 0xffa10000) {
		field->flags |= HID_MAIN_ITEM_RELATIVE | HID_MAIN_ITEM_VARIABLE;
		field->logical_minimum = -127;
		field->logical_maximum = 127;

		switch (usage->hid & HID_USAGE) {
		case 0x0000:
			hid_map_usage(hi, usage, bit, max, EV_REL, REL_HWHEEL);
			return 1;
		case 0x0001:
			hid_map_usage(hi, usage, bit, max, EV_REL, REL_WHEEL);
			return 1;
		default:
			return -1;
		}
	}

	return 0;
}