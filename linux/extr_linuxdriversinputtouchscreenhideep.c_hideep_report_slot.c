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
struct input_dev {int dummy; } ;
struct hideep_event {int index; int flag; int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int HIDEEP_MT_RELEASED ; 
 int /*<<< orphan*/  __GET_MT_TOOL_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hideep_report_slot(struct input_dev *input,
			       const struct hideep_event *event)
{
	input_mt_slot(input, event->index & 0x0f);
	input_mt_report_slot_state(input,
				   __GET_MT_TOOL_TYPE(event->type),
				   !(event->flag & HIDEEP_MT_RELEASED));
	if (!(event->flag & HIDEEP_MT_RELEASED)) {
		input_report_abs(input, ABS_MT_POSITION_X,
				 le16_to_cpup(&event->x));
		input_report_abs(input, ABS_MT_POSITION_Y,
				 le16_to_cpup(&event->y));
		input_report_abs(input, ABS_MT_PRESSURE,
				 le16_to_cpup(&event->z));
		input_report_abs(input, ABS_MT_TOUCH_MAJOR, event->w);
	}
}