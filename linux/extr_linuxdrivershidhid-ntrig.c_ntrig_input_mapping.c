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
struct ntrig_data {int sensor_logical_width; int sensor_physical_width; int activation_width; int min_width; int sensor_logical_height; int sensor_physical_height; int activation_height; int min_height; } ;
struct hid_usage {int hid; } ;
struct hid_input {int /*<<< orphan*/  input; } ;
struct hid_field {int logical_minimum; int logical_maximum; int physical_maximum; int physical_minimum; scalar_t__ physical; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  EV_ABS ; 
#define  HID_DG_CONTACTID 137 
#define  HID_DG_CONTACTMAX 136 
#define  HID_DG_DEVICEINDEX 135 
#define  HID_DG_HEIGHT 134 
#define  HID_DG_INPUTMODE 133 
#define  HID_DG_WIDTH 132 
#define  HID_GD_X 131 
#define  HID_GD_Y 130 
#define  HID_UP_DIGITIZER 129 
#define  HID_UP_GENDESK 128 
 int HID_USAGE_PAGE ; 
 int activation_height ; 
 int activation_width ; 
 struct ntrig_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min_height ; 
 int min_width ; 

__attribute__((used)) static int ntrig_input_mapping(struct hid_device *hdev, struct hid_input *hi,
			       struct hid_field *field, struct hid_usage *usage,
			       unsigned long **bit, int *max)
{
	struct ntrig_data *nd = hid_get_drvdata(hdev);

	/* No special mappings needed for the pen and single touch */
	if (field->physical)
		return 0;

	switch (usage->hid & HID_USAGE_PAGE) {
	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_X);
			input_set_abs_params(hi->input, ABS_X,
					field->logical_minimum,
					field->logical_maximum, 0, 0);

			if (!nd->sensor_logical_width) {
				nd->sensor_logical_width =
					field->logical_maximum -
					field->logical_minimum;
				nd->sensor_physical_width =
					field->physical_maximum -
					field->physical_minimum;
				nd->activation_width = activation_width *
					nd->sensor_logical_width /
					nd->sensor_physical_width;
				nd->min_width = min_width *
					nd->sensor_logical_width /
					nd->sensor_physical_width;
			}
			return 1;
		case HID_GD_Y:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_Y);
			input_set_abs_params(hi->input, ABS_Y,
					field->logical_minimum,
					field->logical_maximum, 0, 0);

			if (!nd->sensor_logical_height) {
				nd->sensor_logical_height =
					field->logical_maximum -
					field->logical_minimum;
				nd->sensor_physical_height =
					field->physical_maximum -
					field->physical_minimum;
				nd->activation_height = activation_height *
					nd->sensor_logical_height /
					nd->sensor_physical_height;
				nd->min_height = min_height *
					nd->sensor_logical_height /
					nd->sensor_physical_height;
			}
			return 1;
		}
		return 0;

	case HID_UP_DIGITIZER:
		switch (usage->hid) {
		/* we do not want to map these for now */
		case HID_DG_CONTACTID: /* Not trustworthy, squelch for now */
		case HID_DG_INPUTMODE:
		case HID_DG_DEVICEINDEX:
		case HID_DG_CONTACTMAX:
			return -1;

		/* width/height mapped on TouchMajor/TouchMinor/Orientation */
		case HID_DG_WIDTH:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MAJOR);
			return 1;
		case HID_DG_HEIGHT:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MINOR);
			input_set_abs_params(hi->input, ABS_MT_ORIENTATION,
					     0, 1, 0, 0);
			return 1;
		}
		return 0;

	case 0xff000000:
		/* we do not want to map these: no input-oriented meaning */
		return -1;
	}

	return 0;
}