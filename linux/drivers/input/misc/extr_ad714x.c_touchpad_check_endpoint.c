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
struct ad714x_touchpad_plat {size_t x_start_stage; size_t x_end_stage; size_t y_start_stage; size_t y_end_stage; } ;
struct ad714x_touchpad_drv {int left_ep; int left_ep_val; int right_ep; int right_ep_val; int top_ep; int top_ep_val; int bottom_ep; int bottom_ep_val; } ;
struct ad714x_chip {int* sensor_val; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_touchpad_drv* touchpad; } ;
struct TYPE_3__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */
 int BOTTOM_END_POINT_DETECTION_LEVEL ; 
 int LEFT_END_POINT_DETECTION_LEVEL ; 
 int LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL ; 
 int RIGHT_END_POINT_DETECTION_LEVEL ; 
 int TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL ; 
 int TOP_END_POINT_DETECTION_LEVEL ; 

__attribute__((used)) static int touchpad_check_endpoint(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	struct ad714x_touchpad_drv *sw  = &ad714x->sw->touchpad[idx];
	int percent_sensor_diff;

	/* left endpoint detect */
	percent_sensor_diff = (ad714x->sensor_val[hw->x_start_stage] -
			ad714x->sensor_val[hw->x_start_stage + 1]) * 100 /
			ad714x->sensor_val[hw->x_start_stage + 1];
	if (!sw->left_ep) {
		if (percent_sensor_diff >= LEFT_END_POINT_DETECTION_LEVEL)  {
			sw->left_ep = 1;
			sw->left_ep_val =
				ad714x->sensor_val[hw->x_start_stage + 1];
		}
	} else {
		if ((percent_sensor_diff < LEFT_END_POINT_DETECTION_LEVEL) &&
		    (ad714x->sensor_val[hw->x_start_stage + 1] >
		     LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL + sw->left_ep_val))
			sw->left_ep = 0;
	}

	/* right endpoint detect */
	percent_sensor_diff = (ad714x->sensor_val[hw->x_end_stage] -
			ad714x->sensor_val[hw->x_end_stage - 1]) * 100 /
			ad714x->sensor_val[hw->x_end_stage - 1];
	if (!sw->right_ep) {
		if (percent_sensor_diff >= RIGHT_END_POINT_DETECTION_LEVEL)  {
			sw->right_ep = 1;
			sw->right_ep_val =
				ad714x->sensor_val[hw->x_end_stage - 1];
		}
	} else {
		if ((percent_sensor_diff < RIGHT_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->x_end_stage - 1] >
		LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL + sw->right_ep_val))
			sw->right_ep = 0;
	}

	/* top endpoint detect */
	percent_sensor_diff = (ad714x->sensor_val[hw->y_start_stage] -
			ad714x->sensor_val[hw->y_start_stage + 1]) * 100 /
			ad714x->sensor_val[hw->y_start_stage + 1];
	if (!sw->top_ep) {
		if (percent_sensor_diff >= TOP_END_POINT_DETECTION_LEVEL)  {
			sw->top_ep = 1;
			sw->top_ep_val =
				ad714x->sensor_val[hw->y_start_stage + 1];
		}
	} else {
		if ((percent_sensor_diff < TOP_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->y_start_stage + 1] >
		TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL + sw->top_ep_val))
			sw->top_ep = 0;
	}

	/* bottom endpoint detect */
	percent_sensor_diff = (ad714x->sensor_val[hw->y_end_stage] -
		ad714x->sensor_val[hw->y_end_stage - 1]) * 100 /
		ad714x->sensor_val[hw->y_end_stage - 1];
	if (!sw->bottom_ep) {
		if (percent_sensor_diff >= BOTTOM_END_POINT_DETECTION_LEVEL)  {
			sw->bottom_ep = 1;
			sw->bottom_ep_val =
				ad714x->sensor_val[hw->y_end_stage - 1];
		}
	} else {
		if ((percent_sensor_diff < BOTTOM_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->y_end_stage - 1] >
		 TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL + sw->bottom_ep_val))
			sw->bottom_ep = 0;
	}

	return sw->left_ep || sw->right_ep || sw->top_ep || sw->bottom_ep;
}