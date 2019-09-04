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
struct psmouse {struct fsp_data* private; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  relbit; } ;
struct fsp_data {scalar_t__ ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_REL ; 
 scalar_t__ FSP_VER_STL3888_C0 ; 
 int /*<<< orphan*/  INPUT_PROP_SEMI_MT ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsp_set_input_params(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct fsp_data *pad = psmouse->private;

	if (pad->ver < FSP_VER_STL3888_C0) {
		__set_bit(BTN_MIDDLE, dev->keybit);
		__set_bit(BTN_BACK, dev->keybit);
		__set_bit(BTN_FORWARD, dev->keybit);
		__set_bit(REL_WHEEL, dev->relbit);
		__set_bit(REL_HWHEEL, dev->relbit);
	} else {
		/*
		 * Hardware prior to Cx performs much better in relative mode;
		 * hence, only enable absolute coordinates output as well as
		 * multi-touch output for the newer hardware.
		 *
		 * Maximum coordinates can be computed as:
		 *
		 *	number of scanlines * 64 - 57
		 *
		 * where number of X/Y scanline lines are 16/12.
		 */
		int abs_x = 967, abs_y = 711;

		__set_bit(EV_ABS, dev->evbit);
		__clear_bit(EV_REL, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);
		__set_bit(BTN_TOOL_FINGER, dev->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);

		input_set_abs_params(dev, ABS_X, 0, abs_x, 0, 0);
		input_set_abs_params(dev, ABS_Y, 0, abs_y, 0, 0);
		input_mt_init_slots(dev, 2, 0);
		input_set_abs_params(dev, ABS_MT_POSITION_X, 0, abs_x, 0, 0);
		input_set_abs_params(dev, ABS_MT_POSITION_Y, 0, abs_y, 0, 0);
	}

	return 0;
}