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
 int HID_UP_CONSUMER ; 
 int HID_UP_LOGIVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_BLUE ; 
 int /*<<< orphan*/  KEY_GREEN ; 
 int /*<<< orphan*/  KEY_NEXT ; 
 int /*<<< orphan*/  KEY_RED ; 
 int /*<<< orphan*/  KEY_TEXT ; 
 int /*<<< orphan*/  KEY_YELLOW ; 
 int /*<<< orphan*/  pl_map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_LOGIVENDOR) {
		switch (usage->hid & HID_USAGE) {
		case 0x05a: pl_map_key_clear(KEY_TEXT);		break;
		case 0x05b: pl_map_key_clear(KEY_RED);		break;
		case 0x05c: pl_map_key_clear(KEY_GREEN);	break;
		case 0x05d: pl_map_key_clear(KEY_YELLOW);	break;
		case 0x05e: pl_map_key_clear(KEY_BLUE);		break;
		default:
			return 0;
		}
		return 1;
	}

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER) {
		switch (usage->hid & HID_USAGE) {
		case 0x0f6: pl_map_key_clear(KEY_NEXT);		break;
		case 0x0fa: pl_map_key_clear(KEY_BACK);		break;
		default:
			return 0;
		}
		return 1;
	}

	return 0;
}