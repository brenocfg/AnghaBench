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
struct goodix_ts_data {int contact_size; int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int GOODIX_MAX_CONTACTS ; 
 int GOODIX_MAX_CONTACT_SIZE ; 
 int /*<<< orphan*/  KEY_LEFTMETA ; 
 int goodix_ts_read_input_report (struct goodix_ts_data*,int*) ; 
 int /*<<< orphan*/  goodix_ts_report_touch_8b (struct goodix_ts_data*,int*) ; 
 int /*<<< orphan*/  goodix_ts_report_touch_9b (struct goodix_ts_data*,int*) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goodix_process_events(struct goodix_ts_data *ts)
{
	u8  point_data[1 + GOODIX_MAX_CONTACT_SIZE * GOODIX_MAX_CONTACTS];
	int touch_num;
	int i;

	touch_num = goodix_ts_read_input_report(ts, point_data);
	if (touch_num < 0)
		return;

	/*
	 * Bit 4 of the first byte reports the status of the capacitive
	 * Windows/Home button.
	 */
	input_report_key(ts->input_dev, KEY_LEFTMETA, point_data[0] & BIT(4));

	for (i = 0; i < touch_num; i++)
		if (ts->contact_size == 9)
			goodix_ts_report_touch_9b(ts,
				&point_data[1 + ts->contact_size * i]);
		else
			goodix_ts_report_touch_8b(ts,
				&point_data[1 + ts->contact_size * i]);

	input_mt_sync_frame(ts->input_dev);
	input_sync(ts->input_dev);
}