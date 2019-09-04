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
#define  CORSAIR_USAGE_M1 132 
#define  CORSAIR_USAGE_M2 131 
#define  CORSAIR_USAGE_M3 130 
#define  CORSAIR_USAGE_MACRO_RECORD_START 129 
#define  CORSAIR_USAGE_MACRO_RECORD_STOP 128 
 int CORSAIR_USAGE_SPECIAL_MAX ; 
 int CORSAIR_USAGE_SPECIAL_MIN ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HID_UP_KEYBOARD ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/ * corsair_gkey_map ; 
 int /*<<< orphan*/ * corsair_profile_keycodes ; 
 int /*<<< orphan*/ * corsair_record_keycodes ; 
 int corsair_usage_to_gkey (int) ; 
 int /*<<< orphan*/  hid_map_usage_clear (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int corsair_input_mapping(struct hid_device *dev,
				 struct hid_input *input,
				 struct hid_field *field,
				 struct hid_usage *usage, unsigned long **bit,
				 int *max)
{
	int gkey;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD)
		return 0;

	gkey = corsair_usage_to_gkey(usage->hid & HID_USAGE);
	if (gkey != 0) {
		hid_map_usage_clear(input, usage, bit, max, EV_KEY,
				    corsair_gkey_map[gkey - 1]);
		return 1;
	}
	if ((usage->hid & HID_USAGE) >= CORSAIR_USAGE_SPECIAL_MIN &&
	    (usage->hid & HID_USAGE) <= CORSAIR_USAGE_SPECIAL_MAX) {
		switch (usage->hid & HID_USAGE) {
		case CORSAIR_USAGE_MACRO_RECORD_START:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[0]);
			return 1;

		case CORSAIR_USAGE_MACRO_RECORD_STOP:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[1]);
			return 1;

		case CORSAIR_USAGE_M1:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[0]);
			return 1;

		case CORSAIR_USAGE_M2:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[1]);
			return 1;

		case CORSAIR_USAGE_M3:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[2]);
			return 1;

		default:
			return -1;
		}
	}

	return 0;
}