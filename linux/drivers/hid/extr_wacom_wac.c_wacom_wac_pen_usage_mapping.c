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
struct wacom_features {int quirks; int device_type; } ;
struct wacom_wac {struct input_dev* pen_input; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct input_dev {int /*<<< orphan*/  evbit; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_LENS ; 
 int /*<<< orphan*/  BTN_TOOL_MOUSE ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
#define  HID_DG_BARRELSWITCH 145 
#define  HID_DG_BARRELSWITCH2 144 
#define  HID_DG_ERASER 143 
#define  HID_DG_INRANGE 142 
#define  HID_DG_INVERT 141 
#define  HID_DG_TILT_X 140 
#define  HID_DG_TILT_Y 139 
#define  HID_DG_TIPPRESSURE 138 
#define  HID_DG_TIPSWITCH 137 
#define  HID_DG_TOOLSERIALNUMBER 136 
#define  HID_DG_TWIST 135 
#define  HID_GD_X 134 
#define  HID_GD_Y 133 
#define  HID_GD_Z 132 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int WACOM_DEVICETYPE_DIRECT ; 
#define  WACOM_HID_WD_DISTANCE 131 
#define  WACOM_HID_WD_FINGERWHEEL 130 
#define  WACOM_HID_WD_SENSE 129 
#define  WACOM_HID_WD_SERIALHI 128 
 int WACOM_QUIRK_AESPEN ; 
 int WACOM_QUIRK_SENSE ; 
 int WACOM_QUIRK_TOOLSERIAL ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_map_usage (struct input_dev*,struct hid_usage*,struct hid_field*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wacom_wac_pen_usage_mapping(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;
	struct input_dev *input = wacom_wac->pen_input;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);

	switch (equivalent_usage) {
	case HID_GD_X:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_X, 4);
		break;
	case HID_GD_Y:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Y, 4);
		break;
	case WACOM_HID_WD_DISTANCE:
	case HID_GD_Z:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_DISTANCE, 0);
		break;
	case HID_DG_TIPPRESSURE:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_PRESSURE, 0);
		break;
	case HID_DG_INRANGE:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOOL_PEN, 0);
		break;
	case HID_DG_INVERT:
		wacom_map_usage(input, usage, field, EV_KEY,
				BTN_TOOL_RUBBER, 0);
		break;
	case HID_DG_TILT_X:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_TILT_X, 0);
		break;
	case HID_DG_TILT_Y:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_TILT_Y, 0);
		break;
	case HID_DG_TWIST:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Z, 0);
		break;
	case HID_DG_ERASER:
	case HID_DG_TIPSWITCH:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOUCH, 0);
		break;
	case HID_DG_BARRELSWITCH:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_STYLUS, 0);
		break;
	case HID_DG_BARRELSWITCH2:
		wacom_map_usage(input, usage, field, EV_KEY, BTN_STYLUS2, 0);
		break;
	case HID_DG_TOOLSERIALNUMBER:
		features->quirks |= WACOM_QUIRK_TOOLSERIAL;
		wacom_map_usage(input, usage, field, EV_MSC, MSC_SERIAL, 0);
		break;
	case WACOM_HID_WD_SENSE:
		features->quirks |= WACOM_QUIRK_SENSE;
		wacom_map_usage(input, usage, field, EV_KEY, BTN_TOOL_PEN, 0);
		break;
	case WACOM_HID_WD_SERIALHI:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_MISC, 0);

		if (!(features->quirks & WACOM_QUIRK_AESPEN)) {
			set_bit(EV_KEY, input->evbit);
			input_set_capability(input, EV_KEY, BTN_TOOL_PEN);
			input_set_capability(input, EV_KEY, BTN_TOOL_RUBBER);
			input_set_capability(input, EV_KEY, BTN_TOOL_BRUSH);
			input_set_capability(input, EV_KEY, BTN_TOOL_PENCIL);
			input_set_capability(input, EV_KEY, BTN_TOOL_AIRBRUSH);
			if (!(features->device_type & WACOM_DEVICETYPE_DIRECT)) {
				input_set_capability(input, EV_KEY, BTN_TOOL_MOUSE);
				input_set_capability(input, EV_KEY, BTN_TOOL_LENS);
			}
		}
		break;
	case WACOM_HID_WD_FINGERWHEEL:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_WHEEL, 0);
		break;
	}
}