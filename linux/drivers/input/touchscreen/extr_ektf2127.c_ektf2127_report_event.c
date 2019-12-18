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
typedef  int u8 ;
struct input_mt_pos {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct ektf2127_ts {int /*<<< orphan*/  input; int /*<<< orphan*/  prop; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EKTF2127_MAX_TOUCHES ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/  ektf2127_parse_coordinates (int const*,unsigned int,struct input_mt_pos*) ; 
 int /*<<< orphan*/  input_mt_assign_slots (int /*<<< orphan*/ ,int*,struct input_mt_pos*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_report_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ektf2127_report_event(struct ektf2127_ts *ts, const u8 *buf)
{
	struct input_mt_pos touches[EKTF2127_MAX_TOUCHES];
	int slots[EKTF2127_MAX_TOUCHES];
	unsigned int touch_count, i;

	touch_count = buf[1] & 0x07;
	if (touch_count > EKTF2127_MAX_TOUCHES) {
		dev_err(&ts->client->dev,
			"Too many touches %d > %d\n",
			touch_count, EKTF2127_MAX_TOUCHES);
		touch_count = EKTF2127_MAX_TOUCHES;
	}

	ektf2127_parse_coordinates(buf, touch_count, touches);
	input_mt_assign_slots(ts->input, slots, touches,
			      touch_count, 0);

	for (i = 0; i < touch_count; i++) {
		input_mt_slot(ts->input, slots[i]);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);
		touchscreen_report_pos(ts->input, &ts->prop,
				       touches[i].x, touches[i].y, true);
	}

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
}