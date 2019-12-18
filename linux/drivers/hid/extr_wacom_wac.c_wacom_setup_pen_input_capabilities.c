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
struct wacom_features {int device_type; int type; int offset_left; int x_max; int offset_right; int offset_top; int y_max; int offset_bottom; int pressure_max; int x_resolution; int y_resolution; int distance_max; int /*<<< orphan*/  distance_fuzz; int /*<<< orphan*/  pressure_fuzz; int /*<<< orphan*/  y_fuzz; int /*<<< orphan*/  x_fuzz; } ;
struct wacom_wac {struct wacom_features features; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
#define  BAMBOO_PAD 177 
#define  BAMBOO_PEN 176 
#define  BAMBOO_PT 175 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_STYLUS3 ; 
 int /*<<< orphan*/  BTN_TOOL_MOUSE ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  CINTIQ 174 
#define  CINTIQ_COMPANION_2 173 
#define  CINTIQ_HYBRID 172 
#define  DTK 171 
#define  DTU 170 
#define  DTUS 169 
#define  DTUSX 168 
 int ENODEV ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
#define  GRAPHIRE 167 
#define  GRAPHIRE_BT 166 
 int HID_GENERIC ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
#define  INTUOS 165 
#define  INTUOS3 164 
#define  INTUOS3L 163 
#define  INTUOS3S 162 
#define  INTUOS4 161 
#define  INTUOS4L 160 
#define  INTUOS4S 159 
#define  INTUOS4WL 158 
#define  INTUOS5 157 
#define  INTUOS5L 156 
#define  INTUOS5S 155 
#define  INTUOSHT 154 
#define  INTUOSHT2 153 
#define  INTUOSHT3_BT 152 
#define  INTUOSP2S_BT 151 
#define  INTUOSP2_BT 150 
#define  INTUOSPL 149 
#define  INTUOSPM 148 
#define  INTUOSPS 147 
#define  MTSCREEN 146 
#define  MTTPC 145 
#define  MTTPC_B 144 
#define  PENPARTNER 143 
#define  PL 142 
#define  PTU 141 
 int /*<<< orphan*/  REL_WHEEL ; 
#define  TABLETPC 140 
#define  TABLETPC2FG 139 
#define  TABLETPCE 138 
#define  WACOM_13HD 137 
#define  WACOM_21UX2 136 
#define  WACOM_22HD 135 
#define  WACOM_24HD 134 
#define  WACOM_24HDT 133 
#define  WACOM_27QHD 132 
#define  WACOM_27QHDT 131 
#define  WACOM_BEE 130 
 int WACOM_DEVICETYPE_DIRECT ; 
 int WACOM_DEVICETYPE_PEN ; 
#define  WACOM_G4 129 
#define  WACOM_MO 128 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_setup_basic_pro_pen (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_setup_cintiq (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_setup_intuos (struct wacom_wac*) ; 

int wacom_setup_pen_input_capabilities(struct input_dev *input_dev,
				   struct wacom_wac *wacom_wac)
{
	struct wacom_features *features = &wacom_wac->features;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	if (!(features->device_type & WACOM_DEVICETYPE_PEN))
		return -ENODEV;

	if (features->device_type & WACOM_DEVICETYPE_DIRECT)
		__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
	else
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	if (features->type == HID_GENERIC) {
		/* setup has already been done; apply otherwise-undetectible quirks */
		input_set_capability(input_dev, EV_KEY, BTN_STYLUS3);
		return 0;
	}

	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(ABS_MISC, input_dev->absbit);

	input_set_abs_params(input_dev, ABS_X, 0 + features->offset_left,
			     features->x_max - features->offset_right,
			     features->x_fuzz, 0);
	input_set_abs_params(input_dev, ABS_Y, 0 + features->offset_top,
			     features->y_max - features->offset_bottom,
			     features->y_fuzz, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0,
		features->pressure_max, features->pressure_fuzz, 0);

	/* penabled devices have fixed resolution for each model */
	input_abs_set_res(input_dev, ABS_X, features->x_resolution);
	input_abs_set_res(input_dev, ABS_Y, features->y_resolution);

	switch (features->type) {
	case GRAPHIRE_BT:
		__clear_bit(ABS_MISC, input_dev->absbit);
		/* fall through */

	case WACOM_MO:
	case WACOM_G4:
		input_set_abs_params(input_dev, ABS_DISTANCE, 0,
					      features->distance_max,
					      features->distance_fuzz, 0);
		/* fall through */

	case GRAPHIRE:
		input_set_capability(input_dev, EV_REL, REL_WHEEL);

		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		__set_bit(BTN_MIDDLE, input_dev->keybit);

		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_MOUSE, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		break;

	case WACOM_27QHD:
	case WACOM_24HD:
	case DTK:
	case WACOM_22HD:
	case WACOM_21UX2:
	case WACOM_BEE:
	case CINTIQ:
	case WACOM_13HD:
	case CINTIQ_HYBRID:
	case CINTIQ_COMPANION_2:
		input_set_abs_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_res(input_dev, ABS_Z, 287);
		wacom_setup_cintiq(wacom_wac);
		break;

	case INTUOS3:
	case INTUOS3L:
	case INTUOS3S:
	case INTUOS4:
	case INTUOS4WL:
	case INTUOS4L:
	case INTUOS4S:
		input_set_abs_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_res(input_dev, ABS_Z, 287);
		/* fall through */

	case INTUOS:
		wacom_setup_intuos(wacom_wac);
		break;

	case INTUOS5:
	case INTUOS5L:
	case INTUOSPM:
	case INTUOSPL:
	case INTUOS5S:
	case INTUOSPS:
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_set_abs_params(input_dev, ABS_DISTANCE, 0,
				      features->distance_max,
				      features->distance_fuzz, 0);

		input_set_abs_params(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_res(input_dev, ABS_Z, 287);

		wacom_setup_intuos(wacom_wac);
		break;

	case WACOM_24HDT:
	case WACOM_27QHDT:
	case MTSCREEN:
	case MTTPC:
	case MTTPC_B:
	case TABLETPC2FG:
	case TABLETPC:
	case TABLETPCE:
		__clear_bit(ABS_MISC, input_dev->absbit);
		/* fall through */

	case DTUS:
	case DTUSX:
	case PL:
	case DTU:
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		break;

	case PTU:
		__set_bit(BTN_STYLUS2, input_dev->keybit);
		/* fall through */

	case PENPARTNER:
		__set_bit(BTN_TOOL_PEN, input_dev->keybit);
		__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
		__set_bit(BTN_STYLUS, input_dev->keybit);
		break;

	case INTUOSHT:
	case BAMBOO_PT:
	case BAMBOO_PEN:
	case INTUOSHT2:
	case INTUOSHT3_BT:
		if (features->type == INTUOSHT2 ||
		    features->type == INTUOSHT3_BT) {
			wacom_setup_basic_pro_pen(wacom_wac);
		} else {
			__clear_bit(ABS_MISC, input_dev->absbit);
			__set_bit(BTN_TOOL_PEN, input_dev->keybit);
			__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
			__set_bit(BTN_STYLUS, input_dev->keybit);
			__set_bit(BTN_STYLUS2, input_dev->keybit);
			input_set_abs_params(input_dev, ABS_DISTANCE, 0,
				      features->distance_max,
				      features->distance_fuzz, 0);
		}
		break;
	case BAMBOO_PAD:
		__clear_bit(ABS_MISC, input_dev->absbit);
		break;
	}
	return 0;
}