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
typedef  int u8 ;
struct raydium_data {int report_size; int contact_size; int* report_data; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 size_t RM_CONTACT_PRESSURE_POS ; 
 size_t RM_CONTACT_STATE_POS ; 
 size_t RM_CONTACT_WIDTH_X_POS ; 
 size_t RM_CONTACT_WIDTH_Y_POS ; 
 size_t RM_CONTACT_X_POS ; 
 size_t RM_CONTACT_Y_POS ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void raydium_mt_event(struct raydium_data *ts)
{
	int i;

	for (i = 0; i < ts->report_size / ts->contact_size; i++) {
		u8 *contact = &ts->report_data[ts->contact_size * i];
		bool state = contact[RM_CONTACT_STATE_POS];
		u8 wx, wy;

		input_mt_slot(ts->input, i);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, state);

		if (!state)
			continue;

		input_report_abs(ts->input, ABS_MT_POSITION_X,
				get_unaligned_le16(&contact[RM_CONTACT_X_POS]));
		input_report_abs(ts->input, ABS_MT_POSITION_Y,
				get_unaligned_le16(&contact[RM_CONTACT_Y_POS]));
		input_report_abs(ts->input, ABS_MT_PRESSURE,
				contact[RM_CONTACT_PRESSURE_POS]);

		wx = contact[RM_CONTACT_WIDTH_X_POS];
		wy = contact[RM_CONTACT_WIDTH_Y_POS];

		input_report_abs(ts->input, ABS_MT_TOUCH_MAJOR, max(wx, wy));
		input_report_abs(ts->input, ABS_MT_TOUCH_MINOR, min(wx, wy));
	}

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
}