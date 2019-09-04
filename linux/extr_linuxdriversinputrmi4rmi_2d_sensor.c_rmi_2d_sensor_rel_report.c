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
struct rmi_2d_axis_alignment {scalar_t__ swap_axes; scalar_t__ flip_y; scalar_t__ flip_x; } ;
struct rmi_2d_sensor {int /*<<< orphan*/  input; struct rmi_2d_axis_alignment axis_align; } ;

/* Variables and functions */
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  RMI_2D_REL_POS_MAX ; 
 int /*<<< orphan*/  RMI_2D_REL_POS_MIN ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (int,int) ; 

void rmi_2d_sensor_rel_report(struct rmi_2d_sensor *sensor, int x, int y)
{
	struct rmi_2d_axis_alignment *axis_align = &sensor->axis_align;

	x = min(RMI_2D_REL_POS_MAX, max(RMI_2D_REL_POS_MIN, (int)x));
	y = min(RMI_2D_REL_POS_MAX, max(RMI_2D_REL_POS_MIN, (int)y));

	if (axis_align->flip_x)
		x = min(RMI_2D_REL_POS_MAX, -x);

	if (axis_align->flip_y)
		y = min(RMI_2D_REL_POS_MAX, -y);

	if (axis_align->swap_axes)
		swap(x, y);

	if (x || y) {
		input_report_rel(sensor->input, REL_X, x);
		input_report_rel(sensor->input, REL_Y, y);
	}
}