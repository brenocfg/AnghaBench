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
struct TYPE_2__ {int clip_x_low; int clip_y_low; scalar_t__ swap_axes; scalar_t__ clip_y_high; scalar_t__ clip_x_high; } ;
struct rmi_2d_sensor {int min_x; int max_x; int min_y; int max_y; int x_mm; int y_mm; int dmax; scalar_t__ sensor_type; scalar_t__ topbuttonpad; scalar_t__ report_rel; int /*<<< orphan*/  nbr_fingers; scalar_t__ kernel_tracking; TYPE_1__ axis_align; scalar_t__ report_abs; struct input_dev* input; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOOL_TYPE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int DMAX ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_REL ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_POINTER ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  INPUT_PROP_TOPBUTTONPAD ; 
 int MT_TOOL_MAX ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (int,scalar_t__) ; 
 scalar_t__ rmi_sensor_touchpad ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void rmi_2d_sensor_set_input_params(struct rmi_2d_sensor *sensor)
{
	struct input_dev *input = sensor->input;
	int res_x;
	int res_y;
	int max_x, max_y;
	int input_flags = 0;

	if (sensor->report_abs) {
		sensor->min_x = sensor->axis_align.clip_x_low;
		if (sensor->axis_align.clip_x_high)
			sensor->max_x = min(sensor->max_x,
				sensor->axis_align.clip_x_high);

		sensor->min_y = sensor->axis_align.clip_y_low;
		if (sensor->axis_align.clip_y_high)
			sensor->max_y = min(sensor->max_y,
				sensor->axis_align.clip_y_high);

		set_bit(EV_ABS, input->evbit);

		max_x = sensor->max_x;
		max_y = sensor->max_y;
		if (sensor->axis_align.swap_axes)
			swap(max_x, max_y);
		input_set_abs_params(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
		input_set_abs_params(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

		if (sensor->x_mm && sensor->y_mm) {
			res_x = (sensor->max_x - sensor->min_x) / sensor->x_mm;
			res_y = (sensor->max_y - sensor->min_y) / sensor->y_mm;
			if (sensor->axis_align.swap_axes)
				swap(res_x, res_y);

			input_abs_set_res(input, ABS_X, res_x);
			input_abs_set_res(input, ABS_Y, res_y);

			input_abs_set_res(input, ABS_MT_POSITION_X, res_x);
			input_abs_set_res(input, ABS_MT_POSITION_Y, res_y);

			if (!sensor->dmax)
				sensor->dmax = DMAX * res_x;
		}

		input_set_abs_params(input, ABS_MT_PRESSURE, 0, 0xff, 0, 0);
		input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0, 0x0f, 0, 0);
		input_set_abs_params(input, ABS_MT_TOUCH_MINOR, 0, 0x0f, 0, 0);
		input_set_abs_params(input, ABS_MT_ORIENTATION, 0, 1, 0, 0);
		input_set_abs_params(input, ABS_MT_TOOL_TYPE,
				     0, MT_TOOL_MAX, 0, 0);

		if (sensor->sensor_type == rmi_sensor_touchpad)
			input_flags = INPUT_MT_POINTER;
		else
			input_flags = INPUT_MT_DIRECT;

		if (sensor->kernel_tracking)
			input_flags |= INPUT_MT_TRACK;

		input_mt_init_slots(input, sensor->nbr_fingers, input_flags);
	}

	if (sensor->report_rel) {
		set_bit(EV_REL, input->evbit);
		set_bit(REL_X, input->relbit);
		set_bit(REL_Y, input->relbit);
	}

	if (sensor->topbuttonpad)
		set_bit(INPUT_PROP_TOPBUTTONPAD, input->propbit);
}