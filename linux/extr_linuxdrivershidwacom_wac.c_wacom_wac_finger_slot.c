#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hid_data {scalar_t__ num_received; scalar_t__ num_expected; int x; int y; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  id; scalar_t__ tipswitch; } ;
struct TYPE_3__ {int touch_max; } ;
struct wacom_wac {struct hid_data hid_data; TYPE_2__* shared; TYPE_1__ features; } ;
struct input_dev {int /*<<< orphan*/  absbit; } ;
struct TYPE_4__ {int /*<<< orphan*/  touch_down; int /*<<< orphan*/  is_touch_on; scalar_t__ has_mute_touch_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int input_mt_get_slot_by_key (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int max (scalar_t__,scalar_t__) ; 
 int min (scalar_t__,scalar_t__) ; 
 scalar_t__ report_touch_events (struct wacom_wac*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_finger_slot(struct wacom_wac *wacom_wac,
		struct input_dev *input)
{
	struct hid_data *hid_data = &wacom_wac->hid_data;
	bool mt = wacom_wac->features.touch_max > 1;
	bool prox = hid_data->tipswitch &&
		    report_touch_events(wacom_wac);

	if (wacom_wac->shared->has_mute_touch_switch &&
	    !wacom_wac->shared->is_touch_on) {
		if (!wacom_wac->shared->touch_down)
			return;
		prox = 0;
	}

	wacom_wac->hid_data.num_received++;
	if (wacom_wac->hid_data.num_received > wacom_wac->hid_data.num_expected)
		return;

	if (mt) {
		int slot;

		slot = input_mt_get_slot_by_key(input, hid_data->id);
		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, prox);
	}
	else {
		input_report_key(input, BTN_TOUCH, prox);
	}

	if (prox) {
		input_report_abs(input, mt ? ABS_MT_POSITION_X : ABS_X,
				 hid_data->x);
		input_report_abs(input, mt ? ABS_MT_POSITION_Y : ABS_Y,
				 hid_data->y);

		if (test_bit(ABS_MT_TOUCH_MAJOR, input->absbit)) {
			input_report_abs(input, ABS_MT_TOUCH_MAJOR, max(hid_data->width, hid_data->height));
			input_report_abs(input, ABS_MT_TOUCH_MINOR, min(hid_data->width, hid_data->height));
			if (hid_data->width != hid_data->height)
				input_report_abs(input, ABS_MT_ORIENTATION, hid_data->width <= hid_data->height ? 0 : 1);
		}
	}
}