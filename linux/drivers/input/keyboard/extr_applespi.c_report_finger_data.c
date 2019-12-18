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
struct tp_finger {int /*<<< orphan*/  orientation; int /*<<< orphan*/  tool_minor; int /*<<< orphan*/  tool_major; int /*<<< orphan*/  touch_minor; int /*<<< orphan*/  touch_major; } ;
struct input_mt_pos {int x; int y; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MINOR ; 
 int MAX_FINGER_ORIENTATION ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_finger_data(struct input_dev *input, int slot,
			       const struct input_mt_pos *pos,
			       const struct tp_finger *f)
{
	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, true);

	input_report_abs(input, ABS_MT_TOUCH_MAJOR,
			 le16_to_int(f->touch_major) << 1);
	input_report_abs(input, ABS_MT_TOUCH_MINOR,
			 le16_to_int(f->touch_minor) << 1);
	input_report_abs(input, ABS_MT_WIDTH_MAJOR,
			 le16_to_int(f->tool_major) << 1);
	input_report_abs(input, ABS_MT_WIDTH_MINOR,
			 le16_to_int(f->tool_minor) << 1);
	input_report_abs(input, ABS_MT_ORIENTATION,
			 MAX_FINGER_ORIENTATION - le16_to_int(f->orientation));
	input_report_abs(input, ABS_MT_POSITION_X, pos->x);
	input_report_abs(input, ABS_MT_POSITION_Y, pos->y);
}