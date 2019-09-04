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
struct input_dev {int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOOL_X ; 
 int /*<<< orphan*/  ABS_MT_TOOL_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int /*<<< orphan*/  MAX_CONTACTS ; 
 int SENSOR_RES_X ; 
 int SENSOR_RES_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sur40_input_setup(struct input_dev *input_dev)
{
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);

	input_set_abs_params(input_dev, ABS_MT_POSITION_X,
			     0, SENSOR_RES_X, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y,
			     0, SENSOR_RES_Y, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_TOOL_X,
			     0, SENSOR_RES_X, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOOL_Y,
			     0, SENSOR_RES_Y, 0, 0);

	/* max value unknown, but major/minor axis
	 * can never be larger than screen */
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR,
			     0, SENSOR_RES_X, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MINOR,
			     0, SENSOR_RES_Y, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);

	input_mt_init_slots(input_dev, MAX_CONTACTS,
			    INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
}