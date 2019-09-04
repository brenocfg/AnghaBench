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
 int /*<<< orphan*/  BTN_MOUSE ; 
 int HID_UP_CONSUMER ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  ez_map_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ez_map_rel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ez_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		return 0;

	switch (usage->hid & HID_USAGE) {
	case 0x230: ez_map_key(BTN_MOUSE);	break;
	case 0x231: ez_map_rel(REL_WHEEL);	break;
	/*
	 * this keyboard has a scrollwheel implemented in
	 * totally broken way. We map this usage temporarily
	 * to HWHEEL and handle it in the event quirk handler
	 */
	case 0x232: ez_map_rel(REL_HWHEEL);	break;
	default:
		return 0;
	}
	return 1;
}