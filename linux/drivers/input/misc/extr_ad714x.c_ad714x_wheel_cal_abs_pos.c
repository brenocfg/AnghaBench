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
struct ad714x_wheel_plat {int end_stage; int start_stage; int max_coord; } ;
struct ad714x_wheel_drv {int highest_stage; int abs_pos; } ;
struct ad714x_chip {int* sensor_val; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_wheel_drv* wheel; } ;
struct TYPE_3__ {struct ad714x_wheel_plat* wheel; } ;

/* Variables and functions */

__attribute__((used)) static void ad714x_wheel_cal_abs_pos(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	struct ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];
	int stage_num = hw->end_stage - hw->start_stage + 1;
	int first_before, highest, first_after;
	int a_param, b_param;

	first_before = (sw->highest_stage + stage_num - 1) % stage_num;
	highest = sw->highest_stage;
	first_after = (sw->highest_stage + stage_num + 1) % stage_num;

	a_param = ad714x->sensor_val[highest] *
		(highest - hw->start_stage) +
		ad714x->sensor_val[first_before] *
		(highest - hw->start_stage - 1) +
		ad714x->sensor_val[first_after] *
		(highest - hw->start_stage + 1);
	b_param = ad714x->sensor_val[highest] +
		ad714x->sensor_val[first_before] +
		ad714x->sensor_val[first_after];

	sw->abs_pos = ((hw->max_coord / (hw->end_stage - hw->start_stage)) *
			a_param) / b_param;

	if (sw->abs_pos > hw->max_coord)
		sw->abs_pos = hw->max_coord;
	else if (sw->abs_pos < 0)
		sw->abs_pos = 0;
}