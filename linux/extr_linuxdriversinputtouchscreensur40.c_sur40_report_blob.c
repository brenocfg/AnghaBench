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
struct sur40_blob {scalar_t__ type; int /*<<< orphan*/  ctr_y; int /*<<< orphan*/  ctr_x; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  bb_size_y; int /*<<< orphan*/  bb_size_x; int /*<<< orphan*/  blob_id; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOOL_X ; 
 int /*<<< orphan*/  ABS_MT_TOOL_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int MAX_CONTACTS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 scalar_t__ SUR40_TOUCH ; 
 int input_mt_get_slot_by_key (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void sur40_report_blob(struct sur40_blob *blob, struct input_dev *input)
{
	int wide, major, minor;
	int bb_size_x, bb_size_y, pos_x, pos_y, ctr_x, ctr_y, slotnum;

	if (blob->type != SUR40_TOUCH)
		return;

	slotnum = input_mt_get_slot_by_key(input, blob->blob_id);
	if (slotnum < 0 || slotnum >= MAX_CONTACTS)
		return;

	bb_size_x = le16_to_cpu(blob->bb_size_x);
	bb_size_y = le16_to_cpu(blob->bb_size_y);

	pos_x = le16_to_cpu(blob->pos_x);
	pos_y = le16_to_cpu(blob->pos_y);

	ctr_x = le16_to_cpu(blob->ctr_x);
	ctr_y = le16_to_cpu(blob->ctr_y);

	input_mt_slot(input, slotnum);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, 1);
	wide = (bb_size_x > bb_size_y);
	major = max(bb_size_x, bb_size_y);
	minor = min(bb_size_x, bb_size_y);

	input_report_abs(input, ABS_MT_POSITION_X, pos_x);
	input_report_abs(input, ABS_MT_POSITION_Y, pos_y);
	input_report_abs(input, ABS_MT_TOOL_X, ctr_x);
	input_report_abs(input, ABS_MT_TOOL_Y, ctr_y);

	/* TODO: use a better orientation measure */
	input_report_abs(input, ABS_MT_ORIENTATION, wide);
	input_report_abs(input, ABS_MT_TOUCH_MAJOR, major);
	input_report_abs(input, ABS_MT_TOUCH_MINOR, minor);
}