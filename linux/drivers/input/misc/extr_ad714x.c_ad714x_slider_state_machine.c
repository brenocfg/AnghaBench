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
struct ad714x_slider_plat {int end_stage; int start_stage; } ;
struct ad714x_slider_drv {int state; int /*<<< orphan*/  input; int /*<<< orphan*/  flt_pos; int /*<<< orphan*/  abs_pos; } ;
struct ad714x_chip {unsigned short h_state; unsigned short c_state; int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_slider_drv* slider; } ;
struct TYPE_3__ {struct ad714x_slider_plat* slider; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
#define  ACTIVE 130 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  IDLE 129 
#define  JITTER 128 
 int /*<<< orphan*/  ad714x_slider_cal_abs_pos (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_cal_flt_pos (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_cal_highest_stage (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_cal_sensor_val (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_use_com_int (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  ad714x_slider_use_thr_int (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad714x_slider_state_machine(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	struct ad714x_slider_drv *sw = &ad714x->sw->slider[idx];
	unsigned short h_state, c_state;
	unsigned short mask;

	mask = ((1 << (hw->end_stage + 1)) - 1) - ((1 << hw->start_stage) - 1);

	h_state = ad714x->h_state & mask;
	c_state = ad714x->c_state & mask;

	switch (sw->state) {
	case IDLE:
		if (h_state) {
			sw->state = JITTER;
			/* In End of Conversion interrupt mode, the AD714X
			 * continuously generates hardware interrupts.
			 */
			ad714x_slider_use_com_int(ad714x, idx);
			dev_dbg(ad714x->dev, "slider %d touched\n", idx);
		}
		break;

	case JITTER:
		if (c_state == mask) {
			ad714x_slider_cal_sensor_val(ad714x, idx);
			ad714x_slider_cal_highest_stage(ad714x, idx);
			ad714x_slider_cal_abs_pos(ad714x, idx);
			sw->flt_pos = sw->abs_pos;
			sw->state = ACTIVE;
		}
		break;

	case ACTIVE:
		if (c_state == mask) {
			if (h_state) {
				ad714x_slider_cal_sensor_val(ad714x, idx);
				ad714x_slider_cal_highest_stage(ad714x, idx);
				ad714x_slider_cal_abs_pos(ad714x, idx);
				ad714x_slider_cal_flt_pos(ad714x, idx);
				input_report_abs(sw->input, ABS_X, sw->flt_pos);
				input_report_key(sw->input, BTN_TOUCH, 1);
			} else {
				/* When the user lifts off the sensor, configure
				 * the AD714X back to threshold interrupt mode.
				 */
				ad714x_slider_use_thr_int(ad714x, idx);
				sw->state = IDLE;
				input_report_key(sw->input, BTN_TOUCH, 0);
				dev_dbg(ad714x->dev, "slider %d released\n",
					idx);
			}
			input_sync(sw->input);
		}
		break;

	default:
		break;
	}
}