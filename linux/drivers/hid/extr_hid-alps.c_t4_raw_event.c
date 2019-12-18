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
typedef  int /*<<< orphan*/  u8 ;
struct t4_input_report {int /*<<< orphan*/  button; TYPE_1__* contact; } ;
struct alps_dev {int max_fingers; unsigned int y_max; unsigned int y_min; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int x_hi; int x_lo; int y_hi; int y_lo; int palm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t4_raw_event(struct alps_dev *hdata, u8 *data, int size)
{
	unsigned int x, y, z;
	int i;
	struct t4_input_report *p_report = (struct t4_input_report *)data;

	if (!data)
		return 0;
	for (i = 0; i < hdata->max_fingers; i++) {
		x = p_report->contact[i].x_hi << 8 | p_report->contact[i].x_lo;
		y = p_report->contact[i].y_hi << 8 | p_report->contact[i].y_lo;
		y = hdata->y_max - y + hdata->y_min;
		z = (p_report->contact[i].palm < 0x80 &&
			p_report->contact[i].palm > 0) * 62;
		if (x == 0xffff) {
			x = 0;
			y = 0;
			z = 0;
		}
		input_mt_slot(hdata->input, i);

		input_mt_report_slot_state(hdata->input,
			MT_TOOL_FINGER, z != 0);

		if (!z)
			continue;

		input_report_abs(hdata->input, ABS_MT_POSITION_X, x);
		input_report_abs(hdata->input, ABS_MT_POSITION_Y, y);
		input_report_abs(hdata->input, ABS_MT_PRESSURE, z);
	}
	input_mt_sync_frame(hdata->input);

	input_report_key(hdata->input, BTN_LEFT, p_report->button);

	input_sync(hdata->input);
	return 1;
}