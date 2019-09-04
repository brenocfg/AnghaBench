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
struct wacom_features {int quirks; } ;
struct wacom_wac {unsigned char* data; TYPE_1__* shared; struct input_dev* pad_input; struct input_dev* touch_input; struct wacom_features features; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  touch_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int WACOM_QUIRK_BBTOUCH_LOWRES ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ report_touch_events (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_wac_finger_count_touches (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_bpt_touch(struct wacom_wac *wacom)
{
	struct wacom_features *features = &wacom->features;
	struct input_dev *input = wacom->touch_input;
	struct input_dev *pad_input = wacom->pad_input;
	unsigned char *data = wacom->data;
	int i;

	if (data[0] != 0x02)
	    return 0;

	for (i = 0; i < 2; i++) {
		int offset = (data[1] & 0x80) ? (8 * i) : (9 * i);
		bool touch = report_touch_events(wacom)
			   && (data[offset + 3] & 0x80);

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		if (touch) {
			int x = get_unaligned_be16(&data[offset + 3]) & 0x7ff;
			int y = get_unaligned_be16(&data[offset + 5]) & 0x7ff;
			if (features->quirks & WACOM_QUIRK_BBTOUCH_LOWRES) {
				x <<= 5;
				y <<= 5;
			}
			input_report_abs(input, ABS_MT_POSITION_X, x);
			input_report_abs(input, ABS_MT_POSITION_Y, y);
		}
	}

	input_mt_sync_frame(input);

	input_report_key(pad_input, BTN_LEFT, (data[1] & 0x08) != 0);
	input_report_key(pad_input, BTN_FORWARD, (data[1] & 0x04) != 0);
	input_report_key(pad_input, BTN_BACK, (data[1] & 0x02) != 0);
	input_report_key(pad_input, BTN_RIGHT, (data[1] & 0x01) != 0);
	wacom->shared->touch_down = wacom_wac_finger_count_touches(wacom);

	return 1;
}