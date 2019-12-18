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
struct wtp_data {scalar_t__ y_size; scalar_t__ flip_y; } ;
struct hidpp_touchpad_raw_xy_finger {scalar_t__ area; scalar_t__ y; scalar_t__ x; scalar_t__ contact_status; int /*<<< orphan*/  finger_id; scalar_t__ contact_type; } ;
struct hidpp_device {int /*<<< orphan*/  input; struct wtp_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int input_mt_get_slot_by_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wtp_touch_event(struct hidpp_device *hidpp,
	struct hidpp_touchpad_raw_xy_finger *touch_report)
{
	struct wtp_data *wd = hidpp->private_data;
	int slot;

	if (!touch_report->finger_id || touch_report->contact_type)
		/* no actual data */
		return;

	slot = input_mt_get_slot_by_key(hidpp->input, touch_report->finger_id);

	input_mt_slot(hidpp->input, slot);
	input_mt_report_slot_state(hidpp->input, MT_TOOL_FINGER,
					touch_report->contact_status);
	if (touch_report->contact_status) {
		input_event(hidpp->input, EV_ABS, ABS_MT_POSITION_X,
				touch_report->x);
		input_event(hidpp->input, EV_ABS, ABS_MT_POSITION_Y,
				wd->flip_y ? wd->y_size - touch_report->y :
					     touch_report->y);
		input_event(hidpp->input, EV_ABS, ABS_MT_PRESSURE,
				touch_report->area);
	}
}