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
struct wacom_wac {unsigned char* data; TYPE_1__* shared; struct input_dev* touch_input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  touch_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ report_touch_events (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_wac_finger_count_touches (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_tpc_mt_touch(struct wacom_wac *wacom)
{
	struct input_dev *input = wacom->touch_input;
	unsigned char *data = wacom->data;
	int i;

	for (i = 0; i < 2; i++) {
		int p = data[1] & (1 << i);
		bool touch = p && report_touch_events(wacom);

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		if (touch) {
			int x = le16_to_cpup((__le16 *)&data[i * 2 + 2]) & 0x7fff;
			int y = le16_to_cpup((__le16 *)&data[i * 2 + 6]) & 0x7fff;

			input_report_abs(input, ABS_MT_POSITION_X, x);
			input_report_abs(input, ABS_MT_POSITION_Y, y);
		}
	}
	input_mt_sync_frame(input);

	/* keep touch state for pen event */
	wacom->shared->touch_down = wacom_wac_finger_count_touches(wacom);

	return 1;
}