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
struct pm {int maxcontacts; TYPE_1__* slots; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void pm_mtevent(struct pm *pm, struct input_dev *input)
{
	int i;

	for (i = 0; i < pm->maxcontacts; ++i) {
		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER,
				pm->slots[i].active);
		if (pm->slots[i].active) {
			input_event(input, EV_ABS, ABS_MT_POSITION_X, pm->slots[i].x);
			input_event(input, EV_ABS, ABS_MT_POSITION_Y, pm->slots[i].y);
		}
	}

	input_mt_report_pointer_emulation(input, true);
	input_sync(input);
}