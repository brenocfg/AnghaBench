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
struct hid_usage {int hid; } ;
struct hid_input {TYPE_1__* input; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_5 ; 
 int /*<<< orphan*/  BTN_6 ; 
 int /*<<< orphan*/  BTN_7 ; 
 int /*<<< orphan*/  BTN_8 ; 
 int /*<<< orphan*/  BTN_9 ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  EV_REP ; 
 int HID_UP_MSVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSDOWN ; 
 int /*<<< orphan*/  KEY_BRIGHTNESSUP ; 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  KEY_DISPLAY_OFF ; 
 int /*<<< orphan*/  KEY_PROG1 ; 
 int /*<<< orphan*/  KEY_WLAN ; 
 int /*<<< orphan*/  ch_map_key_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ch_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		return 0;

	set_bit(EV_REP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	case 0xff01: ch_map_key_clear(BTN_1);	break;
	case 0xff02: ch_map_key_clear(BTN_2);	break;
	case 0xff03: ch_map_key_clear(BTN_3);	break;
	case 0xff04: ch_map_key_clear(BTN_4);	break;
	case 0xff05: ch_map_key_clear(BTN_5);	break;
	case 0xff06: ch_map_key_clear(BTN_6);	break;
	case 0xff07: ch_map_key_clear(BTN_7);	break;
	case 0xff08: ch_map_key_clear(BTN_8);	break;
	case 0xff09: ch_map_key_clear(BTN_9);	break;
	case 0xff0a: ch_map_key_clear(BTN_A);	break;
	case 0xff0b: ch_map_key_clear(BTN_B);	break;
	case 0x00f1: ch_map_key_clear(KEY_WLAN);	break;
	case 0x00f2: ch_map_key_clear(KEY_BRIGHTNESSDOWN);	break;
	case 0x00f3: ch_map_key_clear(KEY_BRIGHTNESSUP);	break;
	case 0x00f4: ch_map_key_clear(KEY_DISPLAY_OFF);	break;
	case 0x00f7: ch_map_key_clear(KEY_CAMERA);	break;
	case 0x00f8: ch_map_key_clear(KEY_PROG1);	break;
	default:
		return 0;
	}
	return 1;
}