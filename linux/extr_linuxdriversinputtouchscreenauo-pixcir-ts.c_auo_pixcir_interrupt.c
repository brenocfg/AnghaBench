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
struct auo_point_t {scalar_t__ coord_x; scalar_t__ coord_y; scalar_t__ area_major; scalar_t__ area_minor; scalar_t__ orientation; } ;
struct auo_pixcir_ts_platdata {int /*<<< orphan*/  gpio_int; } ;
struct auo_pixcir_ts {int /*<<< orphan*/  stopped; int /*<<< orphan*/  wait; scalar_t__ touch_ind_mode; int /*<<< orphan*/  input; struct auo_pixcir_ts_platdata* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  AUO_PIXCIR_PENUP_TIMEOUT_MS ; 
 int AUO_PIXCIR_REPORT_POINTS ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int auo_pixcir_collect_data (struct auo_pixcir_ts*,struct auo_point_t*) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t auo_pixcir_interrupt(int irq, void *dev_id)
{
	struct auo_pixcir_ts *ts = dev_id;
	const struct auo_pixcir_ts_platdata *pdata = ts->pdata;
	struct auo_point_t point[AUO_PIXCIR_REPORT_POINTS];
	int i;
	int ret;
	int fingers = 0;
	int abs = -1;

	while (!ts->stopped) {

		/* check for up event in touch touch_ind_mode */
		if (ts->touch_ind_mode) {
			if (gpio_get_value(pdata->gpio_int) == 0) {
				input_mt_sync(ts->input);
				input_report_key(ts->input, BTN_TOUCH, 0);
				input_sync(ts->input);
				break;
			}
		}

		ret = auo_pixcir_collect_data(ts, point);
		if (ret < 0) {
			/* we want to loop only in touch_ind_mode */
			if (!ts->touch_ind_mode)
				break;

			wait_event_timeout(ts->wait, ts->stopped,
				msecs_to_jiffies(AUO_PIXCIR_PENUP_TIMEOUT_MS));
			continue;
		}

		for (i = 0; i < AUO_PIXCIR_REPORT_POINTS; i++) {
			if (point[i].coord_x > 0 || point[i].coord_y > 0) {
				input_report_abs(ts->input, ABS_MT_POSITION_X,
						 point[i].coord_x);
				input_report_abs(ts->input, ABS_MT_POSITION_Y,
						 point[i].coord_y);
				input_report_abs(ts->input, ABS_MT_TOUCH_MAJOR,
						 point[i].area_major);
				input_report_abs(ts->input, ABS_MT_TOUCH_MINOR,
						 point[i].area_minor);
				input_report_abs(ts->input, ABS_MT_ORIENTATION,
						 point[i].orientation);
				input_mt_sync(ts->input);

				/* use first finger as source for singletouch */
				if (fingers == 0)
					abs = i;

				/* number of touch points could also be queried
				 * via i2c but would require an additional call
				 */
				fingers++;
			}
		}

		input_report_key(ts->input, BTN_TOUCH, fingers > 0);

		if (abs > -1) {
			input_report_abs(ts->input, ABS_X, point[abs].coord_x);
			input_report_abs(ts->input, ABS_Y, point[abs].coord_y);
		}

		input_sync(ts->input);

		/* we want to loop only in touch_ind_mode */
		if (!ts->touch_ind_mode)
			break;

		wait_event_timeout(ts->wait, ts->stopped,
				 msecs_to_jiffies(AUO_PIXCIR_PENUP_TIMEOUT_MS));
	}

	return IRQ_HANDLED;
}