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
struct touchscreen_properties {void* swap_x_y; void* invert_y; void* invert_x; void* max_y; void* max_x; } ;
struct TYPE_2__ {struct device* parent; } ;
struct input_dev {struct input_absinfo* absinfo; TYPE_1__ dev; } ;
struct input_absinfo {scalar_t__ minimum; int /*<<< orphan*/  maximum; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ABS_MT_POSITION_X ; 
 unsigned int ABS_MT_POSITION_Y ; 
 unsigned int ABS_MT_PRESSURE ; 
 unsigned int ABS_PRESSURE ; 
 unsigned int ABS_X ; 
 unsigned int ABS_Y ; 
 void* device_property_read_bool (struct device*,char*) ; 
 void* input_abs_get_fuzz (struct input_dev*,unsigned int) ; 
 void* input_abs_get_max (struct input_dev*,unsigned int) ; 
 void* input_abs_get_min (struct input_dev*,unsigned int) ; 
 int /*<<< orphan*/  input_alloc_absinfo (struct input_dev*) ; 
 int /*<<< orphan*/  swap (struct input_absinfo,struct input_absinfo) ; 
 int touchscreen_get_prop_u32 (struct device*,char*,void*,unsigned int*) ; 
 int /*<<< orphan*/  touchscreen_set_params (struct input_dev*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

void touchscreen_parse_properties(struct input_dev *input, bool multitouch,
				  struct touchscreen_properties *prop)
{
	struct device *dev = input->dev.parent;
	struct input_absinfo *absinfo;
	unsigned int axis;
	unsigned int minimum, maximum, fuzz;
	bool data_present;

	input_alloc_absinfo(input);
	if (!input->absinfo)
		return;

	axis = multitouch ? ABS_MT_POSITION_X : ABS_X;
	data_present = touchscreen_get_prop_u32(dev, "touchscreen-min-x",
						input_abs_get_min(input, axis),
						&minimum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-size-x",
						input_abs_get_max(input,
								  axis) + 1,
						&maximum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-fuzz-x",
						input_abs_get_fuzz(input, axis),
						&fuzz);
	if (data_present)
		touchscreen_set_params(input, axis, minimum, maximum - 1, fuzz);

	axis = multitouch ? ABS_MT_POSITION_Y : ABS_Y;
	data_present = touchscreen_get_prop_u32(dev, "touchscreen-min-y",
						input_abs_get_min(input, axis),
						&minimum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-size-y",
						input_abs_get_max(input,
								  axis) + 1,
						&maximum) |
		       touchscreen_get_prop_u32(dev, "touchscreen-fuzz-y",
						input_abs_get_fuzz(input, axis),
						&fuzz);
	if (data_present)
		touchscreen_set_params(input, axis, minimum, maximum - 1, fuzz);

	axis = multitouch ? ABS_MT_PRESSURE : ABS_PRESSURE;
	data_present = touchscreen_get_prop_u32(dev,
						"touchscreen-max-pressure",
						input_abs_get_max(input, axis),
						&maximum) |
		       touchscreen_get_prop_u32(dev,
						"touchscreen-fuzz-pressure",
						input_abs_get_fuzz(input, axis),
						&fuzz);
	if (data_present)
		touchscreen_set_params(input, axis, 0, maximum, fuzz);

	if (!prop)
		return;

	axis = multitouch ? ABS_MT_POSITION_X : ABS_X;

	prop->max_x = input_abs_get_max(input, axis);
	prop->max_y = input_abs_get_max(input, axis + 1);

	prop->invert_x =
		device_property_read_bool(dev, "touchscreen-inverted-x");
	if (prop->invert_x) {
		absinfo = &input->absinfo[axis];
		absinfo->maximum -= absinfo->minimum;
		absinfo->minimum = 0;
	}

	prop->invert_y =
		device_property_read_bool(dev, "touchscreen-inverted-y");
	if (prop->invert_y) {
		absinfo = &input->absinfo[axis + 1];
		absinfo->maximum -= absinfo->minimum;
		absinfo->minimum = 0;
	}

	prop->swap_x_y =
		device_property_read_bool(dev, "touchscreen-swapped-x-y");
	if (prop->swap_x_y)
		swap(input->absinfo[axis], input->absinfo[axis + 1]);
}