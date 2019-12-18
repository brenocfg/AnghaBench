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
struct wacom_features {int /*<<< orphan*/  device_type; int /*<<< orphan*/  numbered_buttons; } ;
struct wacom_wac {int has_mute_touch_switch; int has_mode_change; int is_direct_mode; struct input_dev* pad_input; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  propbit; } ;
struct hid_usage {int /*<<< orphan*/  code; int /*<<< orphan*/  type; int /*<<< orphan*/  hid; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  INPUT_PROP_ACCELEROMETER ; 
 int /*<<< orphan*/  KEY_BUTTONCONFIG ; 
 int /*<<< orphan*/  KEY_CONTROLPANEL ; 
 int /*<<< orphan*/  KEY_ONSCREEN_KEYBOARD ; 
 int /*<<< orphan*/  SW_MUTE_DEVICE ; 
 int /*<<< orphan*/  WACOM_DEVICETYPE_PAD ; 
#define  WACOM_HID_WD_ACCELEROMETER_X 147 
#define  WACOM_HID_WD_ACCELEROMETER_Y 146 
#define  WACOM_HID_WD_ACCELEROMETER_Z 145 
#define  WACOM_HID_WD_BUTTONCENTER 144 
#define  WACOM_HID_WD_BUTTONCONFIG 143 
#define  WACOM_HID_WD_BUTTONDOWN 142 
#define  WACOM_HID_WD_BUTTONHOME 141 
#define  WACOM_HID_WD_BUTTONLEFT 140 
#define  WACOM_HID_WD_BUTTONRIGHT 139 
#define  WACOM_HID_WD_BUTTONUP 138 
#define  WACOM_HID_WD_CONTROLPANEL 137 
#define  WACOM_HID_WD_EXPRESSKEY00 136 
#define  WACOM_HID_WD_MODE_CHANGE 135 
#define  WACOM_HID_WD_MUTE_DEVICE 134 
#define  WACOM_HID_WD_ONSCREEN_KEYBOARD 133 
#define  WACOM_HID_WD_TOUCHONOFF 132 
#define  WACOM_HID_WD_TOUCHRING 131 
#define  WACOM_HID_WD_TOUCHRINGSTATUS 130 
#define  WACOM_HID_WD_TOUCHSTRIP 129 
#define  WACOM_HID_WD_TOUCHSTRIP2 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_map_usage (struct input_dev*,struct hid_usage*,struct hid_field*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_numbered_button_to_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_pad_usage_mapping(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;
	struct input_dev *input = wacom_wac->pad_input;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);

	switch (equivalent_usage) {
	case WACOM_HID_WD_ACCELEROMETER_X:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_X, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_ACCELEROMETER_Y:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Y, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_ACCELEROMETER_Z:
		__set_bit(INPUT_PROP_ACCELEROMETER, input->propbit);
		wacom_map_usage(input, usage, field, EV_ABS, ABS_Z, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_BUTTONCENTER:
	case WACOM_HID_WD_BUTTONHOME:
	case WACOM_HID_WD_BUTTONUP:
	case WACOM_HID_WD_BUTTONDOWN:
	case WACOM_HID_WD_BUTTONLEFT:
	case WACOM_HID_WD_BUTTONRIGHT:
		wacom_map_usage(input, usage, field, EV_KEY,
				wacom_numbered_button_to_key(features->numbered_buttons),
				0);
		features->numbered_buttons++;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_TOUCHONOFF:
	case WACOM_HID_WD_MUTE_DEVICE:
		/*
		 * This usage, which is used to mute touch events, comes
		 * from the pad packet, but is reported on the touch
		 * interface. Because the touch interface may not have
		 * been created yet, we cannot call wacom_map_usage(). In
		 * order to process this usage when we receive it, we set
		 * the usage type and code directly.
		 */
		wacom_wac->has_mute_touch_switch = true;
		usage->type = EV_SW;
		usage->code = SW_MUTE_DEVICE;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_TOUCHSTRIP:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_RX, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_TOUCHSTRIP2:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_RY, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_TOUCHRING:
		wacom_map_usage(input, usage, field, EV_ABS, ABS_WHEEL, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_TOUCHRINGSTATUS:
		/*
		 * Only set up type/code association. Completely mapping
		 * this usage may overwrite the axis resolution and range.
		 */
		usage->type = EV_ABS;
		usage->code = ABS_WHEEL;
		set_bit(EV_ABS, input->evbit);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_BUTTONCONFIG:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_BUTTONCONFIG, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_ONSCREEN_KEYBOARD:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_ONSCREEN_KEYBOARD, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_CONTROLPANEL:
		wacom_map_usage(input, usage, field, EV_KEY, KEY_CONTROLPANEL, 0);
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	case WACOM_HID_WD_MODE_CHANGE:
		/* do not overwrite previous data */
		if (!wacom_wac->has_mode_change) {
			wacom_wac->has_mode_change = true;
			wacom_wac->is_direct_mode = true;
		}
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	}

	switch (equivalent_usage & 0xfffffff0) {
	case WACOM_HID_WD_EXPRESSKEY00:
		wacom_map_usage(input, usage, field, EV_KEY,
				wacom_numbered_button_to_key(features->numbered_buttons),
				0);
		features->numbered_buttons++;
		features->device_type |= WACOM_DEVICETYPE_PAD;
		break;
	}
}