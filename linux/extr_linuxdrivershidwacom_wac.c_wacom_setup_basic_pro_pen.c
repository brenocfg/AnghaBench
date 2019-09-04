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
struct TYPE_2__ {int /*<<< orphan*/  distance_fuzz; int /*<<< orphan*/  distance_max; } ;
struct wacom_wac {TYPE_1__ features; struct input_dev* pen_input; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_setup_basic_pro_pen(struct wacom_wac *wacom_wac)
{
	struct input_dev *input_dev = wacom_wac->pen_input;

	input_set_capability(input_dev, EV_MSC, MSC_SERIAL);

	__set_bit(BTN_TOOL_PEN, input_dev->keybit);
	__set_bit(BTN_STYLUS, input_dev->keybit);
	__set_bit(BTN_STYLUS2, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_DISTANCE,
			     0, wacom_wac->features.distance_max, wacom_wac->features.distance_fuzz, 0);
}