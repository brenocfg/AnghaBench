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
struct input_mt_slot {int dummy; } ;
struct input_mt {int trkid; int num_slots; struct input_mt_slot* slots; } ;
struct asus_drvdata {TYPE_2__* input; TYPE_1__* tp; } ;
struct TYPE_4__ {struct input_mt* mt; } ;
struct TYPE_3__ {int contact_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int TRKID_SGN ; 
 int input_mt_get_value (struct input_mt_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asus_report_tool_width(struct asus_drvdata *drvdat)
{
	struct input_mt *mt = drvdat->input->mt;
	struct input_mt_slot *oldest;
	int oldid, count, i;

	if (drvdat->tp->contact_size < 5)
		return;

	oldest = NULL;
	oldid = mt->trkid;
	count = 0;

	for (i = 0; i < mt->num_slots; ++i) {
		struct input_mt_slot *ps = &mt->slots[i];
		int id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);

		if (id < 0)
			continue;
		if ((id - oldid) & TRKID_SGN) {
			oldest = ps;
			oldid = id;
		}
		count++;
	}

	if (oldest) {
		input_report_abs(drvdat->input, ABS_TOOL_WIDTH,
			input_mt_get_value(oldest, ABS_MT_TOUCH_MAJOR));
	}
}