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
struct rmi_2d_sensor_abs_object {scalar_t__ type; void* y; void* x; } ;
struct rmi_2d_axis_alignment {scalar_t__ clip_y_high; scalar_t__ clip_x_high; int /*<<< orphan*/  clip_y_low; int /*<<< orphan*/  clip_x_low; scalar_t__ offset_y; scalar_t__ offset_x; scalar_t__ swap_axes; scalar_t__ flip_y; scalar_t__ flip_x; } ;
struct rmi_2d_sensor {TYPE_1__* tracking_pos; void* max_y; void* max_x; struct rmi_2d_axis_alignment axis_align; } ;
struct TYPE_2__ {void* y; void* x; } ;

/* Variables and functions */
 scalar_t__ RMI_2D_OBJECT_NONE ; 
 void* max (int /*<<< orphan*/ ,void*) ; 
 void* min (void*,void*) ; 
 int /*<<< orphan*/  swap (void*,void*) ; 

void rmi_2d_sensor_abs_process(struct rmi_2d_sensor *sensor,
				struct rmi_2d_sensor_abs_object *obj,
				int slot)
{
	struct rmi_2d_axis_alignment *axis_align = &sensor->axis_align;

	/* we keep the previous values if the finger is released */
	if (obj->type == RMI_2D_OBJECT_NONE)
		return;

	if (axis_align->flip_x)
		obj->x = sensor->max_x - obj->x;

	if (axis_align->flip_y)
		obj->y = sensor->max_y - obj->y;

	if (axis_align->swap_axes)
		swap(obj->x, obj->y);

	/*
	 * Here checking if X offset or y offset are specified is
	 * redundant. We just add the offsets or clip the values.
	 *
	 * Note: offsets need to be applied before clipping occurs,
	 * or we could get funny values that are outside of
	 * clipping boundaries.
	 */
	obj->x += axis_align->offset_x;
	obj->y += axis_align->offset_y;

	obj->x =  max(axis_align->clip_x_low, obj->x);
	obj->y =  max(axis_align->clip_y_low, obj->y);

	if (axis_align->clip_x_high)
		obj->x = min(sensor->max_x, obj->x);

	if (axis_align->clip_y_high)
		obj->y =  min(sensor->max_y, obj->y);

	sensor->tracking_pos[slot].x = obj->x;
	sensor->tracking_pos[slot].y = obj->y;
}