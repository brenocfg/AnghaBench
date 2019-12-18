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
struct input_polled_dev {struct input_dev* input; struct gpio_mouse* private; } ;
struct input_dev {int dummy; } ;
struct gpio_mouse {scalar_t__ up; scalar_t__ down; scalar_t__ left; scalar_t__ right; scalar_t__ bright; scalar_t__ bmiddle; scalar_t__ bleft; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int gpiod_get_value (scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gpio_mouse_scan(struct input_polled_dev *dev)
{
	struct gpio_mouse *gpio = dev->private;
	struct input_dev *input = dev->input;
	int x, y;

	if (gpio->bleft)
		input_report_key(input, BTN_LEFT,
				 gpiod_get_value(gpio->bleft));
	if (gpio->bmiddle)
		input_report_key(input, BTN_MIDDLE,
				 gpiod_get_value(gpio->bmiddle));
	if (gpio->bright)
		input_report_key(input, BTN_RIGHT,
				 gpiod_get_value(gpio->bright));

	x = gpiod_get_value(gpio->right) - gpiod_get_value(gpio->left);
	y = gpiod_get_value(gpio->down) - gpiod_get_value(gpio->up);

	input_report_rel(input, REL_X, x);
	input_report_rel(input, REL_Y, y);
	input_sync(input);
}