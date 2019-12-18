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
struct wacom_features {int type; scalar_t__ numbered_buttons; int device_type; int /*<<< orphan*/  oPid; } ;
struct wacom_wac {struct input_dev* pad_input; struct wacom_features features; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  propbit; TYPE_1__* absinfo; } ;
struct TYPE_2__ {scalar_t__ maximum; scalar_t__ minimum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 size_t ABS_RX ; 
 size_t ABS_RY ; 
 size_t ABS_THROTTLE ; 
 size_t ABS_WHEEL ; 
 size_t ABS_X ; 
 size_t ABS_Y ; 
 size_t ABS_Z ; 
#define  BAMBOO_PT 163 
#define  BAMBOO_TOUCH 162 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
#define  CINTIQ 161 
#define  CINTIQ_COMPANION_2 160 
#define  CINTIQ_HYBRID 159 
#define  DTK 158 
#define  DTUS 157 
 int ENODEV ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
#define  GRAPHIRE_BT 156 
#define  HID_GENERIC 155 
 int /*<<< orphan*/  INPUT_PROP_ACCELEROMETER ; 
#define  INTUOS3 154 
#define  INTUOS3L 153 
#define  INTUOS3S 152 
#define  INTUOS4 151 
#define  INTUOS4L 150 
#define  INTUOS4S 149 
#define  INTUOS4WL 148 
#define  INTUOS5 147 
#define  INTUOS5L 146 
#define  INTUOS5S 145 
#define  INTUOSHT 144 
#define  INTUOSHT2 143 
#define  INTUOSHT3_BT 142 
#define  INTUOSP2S_BT 141 
#define  INTUOSP2_BT 140 
#define  INTUOSPL 139 
#define  INTUOSPM 138 
#define  INTUOSPS 137 
 int /*<<< orphan*/  KEY_BUTTONCONFIG ; 
 int /*<<< orphan*/  KEY_CONTROLPANEL ; 
 int /*<<< orphan*/  KEY_INFO ; 
 int /*<<< orphan*/  KEY_ONSCREEN_KEYBOARD ; 
 int /*<<< orphan*/  KEY_PROG1 ; 
 int /*<<< orphan*/  KEY_PROG2 ; 
 int /*<<< orphan*/  KEY_PROG3 ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
#define  REMOTE 136 
#define  WACOM_13HD 135 
#define  WACOM_21UX2 134 
#define  WACOM_22HD 133 
#define  WACOM_24HD 132 
#define  WACOM_27QHD 131 
#define  WACOM_BEE 130 
 int WACOM_DEVICETYPE_PAD ; 
#define  WACOM_G4 129 
#define  WACOM_MO 128 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,size_t,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,size_t,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_setup_numbered_buttons (struct input_dev*,scalar_t__) ; 

int wacom_setup_pad_input_capabilities(struct input_dev *input_dev,
				   struct wacom_wac *wacom_wac)
{
	struct wacom_features *features = &wacom_wac->features;

	if ((features->type == HID_GENERIC) && features->numbered_buttons > 0)
		features->device_type |= WACOM_DEVICETYPE_PAD;

	if (!(features->device_type & WACOM_DEVICETYPE_PAD))
		return -ENODEV;

	if (features->type == REMOTE && input_dev == wacom_wac->pad_input)
		return -ENODEV;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	/* kept for making legacy xf86-input-wacom working with the wheels */
	__set_bit(ABS_MISC, input_dev->absbit);

	/* kept for making legacy xf86-input-wacom accepting the pad */
	if (!(input_dev->absinfo && (input_dev->absinfo[ABS_X].minimum ||
	      input_dev->absinfo[ABS_X].maximum)))
		input_set_abs_params(input_dev, ABS_X, 0, 1, 0, 0);
	if (!(input_dev->absinfo && (input_dev->absinfo[ABS_Y].minimum ||
	      input_dev->absinfo[ABS_Y].maximum)))
		input_set_abs_params(input_dev, ABS_Y, 0, 1, 0, 0);

	/* kept for making udev and libwacom accepting the pad */
	__set_bit(BTN_STYLUS, input_dev->keybit);

	wacom_setup_numbered_buttons(input_dev, features->numbered_buttons);

	switch (features->type) {

	case CINTIQ_HYBRID:
	case CINTIQ_COMPANION_2:
	case DTK:
	case DTUS:
	case GRAPHIRE_BT:
		break;

	case WACOM_MO:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		break;

	case WACOM_G4:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		input_set_capability(input_dev, EV_REL, REL_WHEEL);
		break;

	case WACOM_24HD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_ONSCREEN_KEYBOARD, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);

		if (!features->oPid)
			__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		input_set_abs_params(input_dev, ABS_THROTTLE, 0, 71, 0, 0);
		break;

	case WACOM_27QHD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_ONSCREEN_KEYBOARD, input_dev->keybit);
		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		if (!features->oPid)
			__set_bit(KEY_CONTROLPANEL, input_dev->keybit);
		input_set_abs_params(input_dev, ABS_X, -2048, 2048, 0, 0);
		input_abs_set_res(input_dev, ABS_X, 1024); /* points/g */
		input_set_abs_params(input_dev, ABS_Y, -2048, 2048, 0, 0);
		input_abs_set_res(input_dev, ABS_Y, 1024);
		input_set_abs_params(input_dev, ABS_Z, -2048, 2048, 0, 0);
		input_abs_set_res(input_dev, ABS_Z, 1024);
		__set_bit(INPUT_PROP_ACCELEROMETER, input_dev->propbit);
		break;

	case WACOM_22HD:
		__set_bit(KEY_PROG1, input_dev->keybit);
		__set_bit(KEY_PROG2, input_dev->keybit);
		__set_bit(KEY_PROG3, input_dev->keybit);

		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);
		/* fall through */

	case WACOM_21UX2:
	case WACOM_BEE:
	case CINTIQ:
		input_set_abs_params(input_dev, ABS_RX, 0, 4096, 0, 0);
		input_set_abs_params(input_dev, ABS_RY, 0, 4096, 0, 0);
		break;

	case WACOM_13HD:
		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		break;

	case INTUOS3:
	case INTUOS3L:
		input_set_abs_params(input_dev, ABS_RY, 0, 4096, 0, 0);
		/* fall through */

	case INTUOS3S:
		input_set_abs_params(input_dev, ABS_RX, 0, 4096, 0, 0);
		break;

	case INTUOS5:
	case INTUOS5L:
	case INTUOSPM:
	case INTUOSPL:
	case INTUOS5S:
	case INTUOSPS:
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		break;

	case INTUOS4WL:
		/*
		 * For Bluetooth devices, the udev rule does not work correctly
		 * for pads unless we add a stylus capability, which forces
		 * ID_INPUT_TABLET to be set.
		 */
		__set_bit(BTN_STYLUS, input_dev->keybit);
		/* fall through */

	case INTUOS4:
	case INTUOS4L:
	case INTUOS4S:
		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		break;

	case INTUOSHT:
	case BAMBOO_PT:
	case BAMBOO_TOUCH:
	case INTUOSHT2:
		__clear_bit(ABS_MISC, input_dev->absbit);

		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_FORWARD, input_dev->keybit);
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);

		break;

	case REMOTE:
		input_set_capability(input_dev, EV_MSC, MSC_SERIAL);
		input_set_abs_params(input_dev, ABS_WHEEL, 0, 71, 0, 0);
		break;

	case INTUOSHT3_BT:
	case HID_GENERIC:
		break;

	default:
		/* no pad supported */
		return -ENODEV;
	}
	return 0;
}