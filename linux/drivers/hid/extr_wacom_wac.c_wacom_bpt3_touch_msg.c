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
struct wacom_features {scalar_t__ type; } ;
struct wacom_wac {struct input_dev* touch_input; struct wacom_features features; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 scalar_t__ INTUOSHT2 ; 
 scalar_t__ INTUOSPS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int WACOM_CONTACT_AREA_SCALE ; 
 int input_abs_get_res (struct input_dev*,int /*<<< orphan*/ ) ; 
 int input_mt_get_slot_by_key (struct input_dev*,unsigned char) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int int_sqrt (int) ; 
 scalar_t__ report_touch_events (struct wacom_wac*) ; 

__attribute__((used)) static void wacom_bpt3_touch_msg(struct wacom_wac *wacom, unsigned char *data)
{
	struct wacom_features *features = &wacom->features;
	struct input_dev *input = wacom->touch_input;
	bool touch = data[1] & 0x80;
	int slot = input_mt_get_slot_by_key(input, data[0]);

	if (slot < 0)
		return;

	touch = touch && report_touch_events(wacom);

	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);

	if (touch) {
		int x = (data[2] << 4) | (data[4] >> 4);
		int y = (data[3] << 4) | (data[4] & 0x0f);
		int width, height;

		if (features->type >= INTUOSPS && features->type <= INTUOSHT2) {
			width  = data[5] * 100;
			height = data[6] * 100;
		} else {
			/*
			 * "a" is a scaled-down area which we assume is
			 * roughly circular and which can be described as:
			 * a=(pi*r^2)/C.
			 */
			int a = data[5];
			int x_res = input_abs_get_res(input, ABS_MT_POSITION_X);
			int y_res = input_abs_get_res(input, ABS_MT_POSITION_Y);
			width = 2 * int_sqrt(a * WACOM_CONTACT_AREA_SCALE);
			height = width * y_res / x_res;
		}

		input_report_abs(input, ABS_MT_POSITION_X, x);
		input_report_abs(input, ABS_MT_POSITION_Y, y);
		input_report_abs(input, ABS_MT_TOUCH_MAJOR, width);
		input_report_abs(input, ABS_MT_TOUCH_MINOR, height);
	}
}