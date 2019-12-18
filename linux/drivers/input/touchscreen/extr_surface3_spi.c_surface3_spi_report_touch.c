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
struct surface3_ts_data_finger {int status; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  tracking_id; } ;
struct surface3_ts_data {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MINOR ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int input_mt_get_slot_by_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void surface3_spi_report_touch(struct surface3_ts_data *ts_data,
				   struct surface3_ts_data_finger *finger)
{
	int st = finger->status & 0x01;
	int slot;

	slot = input_mt_get_slot_by_key(ts_data->input_dev,
				get_unaligned_le16(&finger->tracking_id));
	if (slot < 0)
		return;

	input_mt_slot(ts_data->input_dev, slot);
	input_mt_report_slot_state(ts_data->input_dev, MT_TOOL_FINGER, st);
	if (st) {
		input_report_abs(ts_data->input_dev,
				 ABS_MT_POSITION_X,
				 get_unaligned_le16(&finger->x));
		input_report_abs(ts_data->input_dev,
				 ABS_MT_POSITION_Y,
				 get_unaligned_le16(&finger->y));
		input_report_abs(ts_data->input_dev,
				 ABS_MT_WIDTH_MAJOR,
				 get_unaligned_le16(&finger->width));
		input_report_abs(ts_data->input_dev,
				 ABS_MT_WIDTH_MINOR,
				 get_unaligned_le16(&finger->height));
	}
}