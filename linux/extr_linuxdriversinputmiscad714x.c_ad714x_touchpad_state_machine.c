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
struct ad714x_touchpad_plat {int x_end_stage; int x_start_stage; int y_end_stage; int y_start_stage; } ;
struct ad714x_touchpad_drv {int state; int /*<<< orphan*/  input; int /*<<< orphan*/  y_flt_pos; int /*<<< orphan*/  x_flt_pos; int /*<<< orphan*/  y_abs_pos; int /*<<< orphan*/  x_abs_pos; } ;
struct ad714x_chip {unsigned short h_state; unsigned short c_state; int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_touchpad_drv* touchpad; } ;
struct TYPE_3__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
#define  ACTIVE 130 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  IDLE 129 
#define  JITTER 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchpad_cal_abs_pos (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_cal_flt_pos (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_cal_highest_stage (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_cal_sensor_val (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_check_endpoint (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_check_second_peak (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_use_com_int (struct ad714x_chip*,int) ; 
 int /*<<< orphan*/  touchpad_use_thr_int (struct ad714x_chip*,int) ; 

__attribute__((used)) static void ad714x_touchpad_state_machine(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	struct ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];
	unsigned short h_state, c_state;
	unsigned short mask;

	mask = (((1 << (hw->x_end_stage + 1)) - 1) -
		((1 << hw->x_start_stage) - 1)) +
		(((1 << (hw->y_end_stage + 1)) - 1) -
		((1 << hw->y_start_stage) - 1));

	h_state = ad714x->h_state & mask;
	c_state = ad714x->c_state & mask;

	switch (sw->state) {
	case IDLE:
		if (h_state) {
			sw->state = JITTER;
			/* In End of Conversion interrupt mode, the AD714X
			 * continuously generates hardware interrupts.
			 */
			touchpad_use_com_int(ad714x, idx);
			dev_dbg(ad714x->dev, "touchpad %d touched\n", idx);
		}
		break;

	case JITTER:
		if (c_state == mask) {
			touchpad_cal_sensor_val(ad714x, idx);
			touchpad_cal_highest_stage(ad714x, idx);
			if ((!touchpad_check_second_peak(ad714x, idx)) &&
				(!touchpad_check_endpoint(ad714x, idx))) {
				dev_dbg(ad714x->dev,
					"touchpad%d, 2 fingers or endpoint\n",
					idx);
				touchpad_cal_abs_pos(ad714x, idx);
				sw->x_flt_pos = sw->x_abs_pos;
				sw->y_flt_pos = sw->y_abs_pos;
				sw->state = ACTIVE;
			}
		}
		break;

	case ACTIVE:
		if (c_state == mask) {
			if (h_state) {
				touchpad_cal_sensor_val(ad714x, idx);
				touchpad_cal_highest_stage(ad714x, idx);
				if ((!touchpad_check_second_peak(ad714x, idx))
				  && (!touchpad_check_endpoint(ad714x, idx))) {
					touchpad_cal_abs_pos(ad714x, idx);
					touchpad_cal_flt_pos(ad714x, idx);
					input_report_abs(sw->input, ABS_X,
						sw->x_flt_pos);
					input_report_abs(sw->input, ABS_Y,
						sw->y_flt_pos);
					input_report_key(sw->input, BTN_TOUCH,
						1);
				}
			} else {
				/* When the user lifts off the sensor, configure
				 * the AD714X back to threshold interrupt mode.
				 */
				touchpad_use_thr_int(ad714x, idx);
				sw->state = IDLE;
				input_report_key(sw->input, BTN_TOUCH, 0);
				dev_dbg(ad714x->dev, "touchpad %d released\n",
					idx);
			}
			input_sync(sw->input);
		}
		break;

	default:
		break;
	}
}