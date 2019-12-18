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
struct wacom_features {int device_type; int type; int touch_max; int x_max; int x_fuzz; int y_max; int y_fuzz; int x_resolution; int y_resolution; int /*<<< orphan*/  pktlen; } ;
struct wacom_wac {TYPE_2__* shared; struct wacom_features features; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  swbit; int /*<<< orphan*/  propbit; } ;
struct TYPE_4__ {int has_mute_touch_switch; TYPE_1__* touch; } ;
struct TYPE_3__ {int product; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
#define  BAMBOO_PAD 148 
#define  BAMBOO_PT 147 
#define  BAMBOO_TOUCH 146 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENODEV ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SW ; 
 int HID_GENERIC ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int /*<<< orphan*/  INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
#define  INTUOS5 145 
#define  INTUOS5L 144 
#define  INTUOS5S 143 
#define  INTUOSHT 142 
#define  INTUOSHT2 141 
#define  INTUOSP2S_BT 140 
#define  INTUOSP2_BT 139 
#define  INTUOSPL 138 
#define  INTUOSPM 137 
#define  INTUOSPS 136 
#define  MTSCREEN 135 
#define  MTTPC 134 
#define  MTTPC_B 133 
 int /*<<< orphan*/  SW_MUTE_DEVICE ; 
#define  TABLETPC 132 
#define  TABLETPC2FG 131 
#define  TABLETPCE 130 
#define  WACOM_24HDT 129 
#define  WACOM_27QHDT 128 
 int WACOM_DEVICETYPE_DIRECT ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int /*<<< orphan*/  WACOM_PKGLEN_BBTOUCH3 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int wacom_setup_touch_input_capabilities(struct input_dev *input_dev,
					 struct wacom_wac *wacom_wac)
{
	struct wacom_features *features = &wacom_wac->features;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	if (!(features->device_type & WACOM_DEVICETYPE_TOUCH))
		return -ENODEV;

	if (features->device_type & WACOM_DEVICETYPE_DIRECT)
		__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
	else
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	if (features->type == HID_GENERIC)
		/* setup has already been done */
		return 0;

	__set_bit(BTN_TOUCH, input_dev->keybit);

	if (features->touch_max == 1) {
		input_set_abs_params(input_dev, ABS_X, 0,
			features->x_max, features->x_fuzz, 0);
		input_set_abs_params(input_dev, ABS_Y, 0,
			features->y_max, features->y_fuzz, 0);
		input_abs_set_res(input_dev, ABS_X,
				  features->x_resolution);
		input_abs_set_res(input_dev, ABS_Y,
				  features->y_resolution);
	}
	else if (features->touch_max > 1) {
		input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0,
			features->x_max, features->x_fuzz, 0);
		input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0,
			features->y_max, features->y_fuzz, 0);
		input_abs_set_res(input_dev, ABS_MT_POSITION_X,
				  features->x_resolution);
		input_abs_set_res(input_dev, ABS_MT_POSITION_Y,
				  features->y_resolution);
	}

	switch (features->type) {
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);

		if (wacom_wac->shared->touch->product == 0x361) {
			input_set_abs_params(input_dev, ABS_MT_POSITION_X,
					     0, 12440, 4, 0);
			input_set_abs_params(input_dev, ABS_MT_POSITION_Y,
					     0, 8640, 4, 0);
		}
		else if (wacom_wac->shared->touch->product == 0x360) {
			input_set_abs_params(input_dev, ABS_MT_POSITION_X,
					     0, 8960, 4, 0);
			input_set_abs_params(input_dev, ABS_MT_POSITION_Y,
					     0, 5920, 4, 0);
		}
		else if (wacom_wac->shared->touch->product == 0x393) {
			input_set_abs_params(input_dev, ABS_MT_POSITION_X,
					     0, 6400, 4, 0);
			input_set_abs_params(input_dev, ABS_MT_POSITION_Y,
					     0, 4000, 4, 0);
		}
		input_abs_set_res(input_dev, ABS_MT_POSITION_X, 40);
		input_abs_set_res(input_dev, ABS_MT_POSITION_Y, 40);

		/* fall through */

	case INTUOS5:
	case INTUOS5L:
	case INTUOSPM:
	case INTUOSPL:
	case INTUOS5S:
	case INTUOSPS:
		input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, features->x_max, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_TOUCH_MINOR, 0, features->y_max, 0, 0);
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_POINTER);
		break;

	case WACOM_24HDT:
		input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, features->x_max, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_WIDTH_MAJOR, 0, features->x_max, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_WIDTH_MINOR, 0, features->y_max, 0, 0);
		input_set_abs_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);
		/* fall through */

	case WACOM_27QHDT:
		if (wacom_wac->shared->touch->product == 0x32C ||
		    wacom_wac->shared->touch->product == 0xF6) {
			input_dev->evbit[0] |= BIT_MASK(EV_SW);
			__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
			wacom_wac->shared->has_mute_touch_switch = true;
		}
		/* fall through */

	case MTSCREEN:
	case MTTPC:
	case MTTPC_B:
	case TABLETPC2FG:
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_DIRECT);
		/*fall through */

	case TABLETPC:
	case TABLETPCE:
		break;

	case INTUOSHT:
	case INTUOSHT2:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
		/* fall through */

	case BAMBOO_PT:
	case BAMBOO_TOUCH:
		if (features->pktlen == WACOM_PKGLEN_BBTOUCH3) {
			input_set_abs_params(input_dev,
				     ABS_MT_TOUCH_MAJOR,
				     0, features->x_max, 0, 0);
			input_set_abs_params(input_dev,
				     ABS_MT_TOUCH_MINOR,
				     0, features->y_max, 0, 0);
		}
		input_mt_init_slots(input_dev, features->touch_max, INPUT_MT_POINTER);
		break;

	case BAMBOO_PAD:
		input_mt_init_slots(input_dev, features->touch_max,
				    INPUT_MT_POINTER);
		__set_bit(BTN_LEFT, input_dev->keybit);
		__set_bit(BTN_RIGHT, input_dev->keybit);
		break;
	}
	return 0;
}