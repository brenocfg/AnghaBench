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
struct ad714x_touchpad_plat {int x_start_stage; int x_end_stage; int y_start_stage; int y_end_stage; } ;
struct ad714x_touchpad_drv {int x_highest_stage; int y_highest_stage; } ;
struct ad714x_chip {int* sensor_val; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_touchpad_drv* touchpad; } ;
struct TYPE_3__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */

__attribute__((used)) static int touchpad_check_second_peak(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	struct ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];
	int i;

	for (i = hw->x_start_stage; i < sw->x_highest_stage; i++) {
		if ((ad714x->sensor_val[i] - ad714x->sensor_val[i + 1])
			> (ad714x->sensor_val[i + 1] / 10))
			return 1;
	}

	for (i = sw->x_highest_stage; i < hw->x_end_stage; i++) {
		if ((ad714x->sensor_val[i + 1] - ad714x->sensor_val[i])
			> (ad714x->sensor_val[i] / 10))
			return 1;
	}

	for (i = hw->y_start_stage; i < sw->y_highest_stage; i++) {
		if ((ad714x->sensor_val[i] - ad714x->sensor_val[i + 1])
			> (ad714x->sensor_val[i + 1] / 10))
			return 1;
	}

	for (i = sw->y_highest_stage; i < hw->y_end_stage; i++) {
		if ((ad714x->sensor_val[i + 1] - ad714x->sensor_val[i])
			> (ad714x->sensor_val[i] / 10))
			return 1;
	}

	return 0;
}