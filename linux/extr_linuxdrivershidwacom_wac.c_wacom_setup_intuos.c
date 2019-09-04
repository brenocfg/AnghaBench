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
struct wacom_wac {struct input_dev* pen_input; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_TOOL_LENS ; 
 int /*<<< orphan*/  BTN_TOOL_MOUSE ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_setup_cintiq (struct wacom_wac*) ; 

__attribute__((used)) static void wacom_setup_intuos(struct wacom_wac *wacom_wac)
{
	struct input_dev *input_dev = wacom_wac->pen_input;

	input_set_capability(input_dev, EV_REL, REL_WHEEL);

	wacom_setup_cintiq(wacom_wac);

	__set_bit(BTN_LEFT, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_SIDE, input_dev->keybit);
	__set_bit(BTN_EXTRA, input_dev->keybit);
	__set_bit(BTN_TOOL_MOUSE, input_dev->keybit);
	__set_bit(BTN_TOOL_LENS, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_RZ, -900, 899, 0, 0);
	input_abs_set_res(input_dev, ABS_RZ, 287);
	input_set_abs_params(input_dev, ABS_THROTTLE, -1023, 1023, 0, 0);
}