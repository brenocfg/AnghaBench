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
struct TYPE_2__ {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REP ; 
 int HID_UP_MSVENDOR ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_CLOSE ; 
 int /*<<< orphan*/  KEY_FORWARD ; 
 int /*<<< orphan*/  KEY_PLAY ; 
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int /*<<< orphan*/  ms_map_key_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_presenter_8k_quirk(struct hid_input *hi, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		return 0;

	set_bit(EV_REP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	case 0xfd08: ms_map_key_clear(KEY_FORWARD);	break;
	case 0xfd09: ms_map_key_clear(KEY_BACK);	break;
	case 0xfd0b: ms_map_key_clear(KEY_PLAYPAUSE);	break;
	case 0xfd0e: ms_map_key_clear(KEY_CLOSE);	break;
	case 0xfd0f: ms_map_key_clear(KEY_PLAY);	break;
	default:
		return 0;
	}
	return 1;
}