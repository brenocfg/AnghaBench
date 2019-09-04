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
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;
struct bcm5974_config {int caps; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  o; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MINOR ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HAS_INTEGRATED_BUTTON ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_POINTER ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  MAX_FINGERS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_events_to_report(struct input_dev *input_dev,
				   const struct bcm5974_config *cfg)
{
	__set_bit(EV_ABS, input_dev->evbit);

	/* for synaptics only */
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 256, 5, 0);
	input_set_abs_params(input_dev, ABS_TOOL_WIDTH, 0, 16, 0, 0);

	/* finger touch area */
	set_abs(input_dev, ABS_MT_TOUCH_MAJOR, &cfg->w);
	set_abs(input_dev, ABS_MT_TOUCH_MINOR, &cfg->w);
	/* finger approach area */
	set_abs(input_dev, ABS_MT_WIDTH_MAJOR, &cfg->w);
	set_abs(input_dev, ABS_MT_WIDTH_MINOR, &cfg->w);
	/* finger orientation */
	set_abs(input_dev, ABS_MT_ORIENTATION, &cfg->o);
	/* finger position */
	set_abs(input_dev, ABS_MT_POSITION_X, &cfg->x);
	set_abs(input_dev, ABS_MT_POSITION_Y, &cfg->y);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_LEFT, input_dev->keybit);

	if (cfg->caps & HAS_INTEGRATED_BUTTON)
		__set_bit(INPUT_PROP_BUTTONPAD, input_dev->propbit);

	input_mt_init_slots(input_dev, MAX_FINGERS,
		INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED | INPUT_MT_TRACK);
}