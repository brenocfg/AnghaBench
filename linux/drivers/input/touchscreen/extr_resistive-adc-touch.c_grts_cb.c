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
typedef  unsigned int u16 ;
struct grts_state {unsigned int pressure_min; int /*<<< orphan*/  input; scalar_t__ pressure; int /*<<< orphan*/  prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_report_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int grts_cb(const void *data, void *private)
{
	const u16 *touch_info = data;
	struct grts_state *st = private;
	unsigned int x, y, press = 0x0;

	/* channel data coming in buffer in the order below */
	x = touch_info[0];
	y = touch_info[1];
	if (st->pressure)
		press = touch_info[2];

	if ((!x && !y) || (st->pressure && (press < st->pressure_min))) {
		/* report end of touch */
		input_report_key(st->input, BTN_TOUCH, 0);
		input_sync(st->input);
		return 0;
	}

	/* report proper touch to subsystem*/
	touchscreen_report_pos(st->input, &st->prop, x, y, false);
	if (st->pressure)
		input_report_abs(st->input, ABS_PRESSURE, press);
	input_report_key(st->input, BTN_TOUCH, 1);
	input_sync(st->input);

	return 0;
}