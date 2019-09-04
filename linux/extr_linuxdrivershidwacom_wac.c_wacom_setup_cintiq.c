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
struct wacom_features {int /*<<< orphan*/  tilt_fuzz; } ;
struct wacom_wac {struct wacom_features features; struct input_dev* pen_input; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_setup_basic_pro_pen (struct wacom_wac*) ; 

__attribute__((used)) static void wacom_setup_cintiq(struct wacom_wac *wacom_wac)
{
	struct input_dev *input_dev = wacom_wac->pen_input;
	struct wacom_features *features = &wacom_wac->features;

	wacom_setup_basic_pro_pen(wacom_wac);

	__set_bit(BTN_TOOL_RUBBER, input_dev->keybit);
	__set_bit(BTN_TOOL_BRUSH, input_dev->keybit);
	__set_bit(BTN_TOOL_PENCIL, input_dev->keybit);
	__set_bit(BTN_TOOL_AIRBRUSH, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_WHEEL, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_X, -64, 63, features->tilt_fuzz, 0);
	input_abs_set_res(input_dev, ABS_TILT_X, 57);
	input_set_abs_params(input_dev, ABS_TILT_Y, -64, 63, features->tilt_fuzz, 0);
	input_abs_set_res(input_dev, ABS_TILT_Y, 57);
}