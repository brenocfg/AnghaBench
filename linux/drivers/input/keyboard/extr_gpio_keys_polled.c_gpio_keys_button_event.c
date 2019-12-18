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
struct input_polled_dev {struct input_dev* input; struct gpio_keys_polled_dev* private; } ;
struct input_dev {int dummy; } ;
struct gpio_keys_polled_dev {int /*<<< orphan*/  abs_axis_seen; int /*<<< orphan*/  rel_axis_seen; } ;
struct gpio_keys_button {int type; int value; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 unsigned int EV_ABS ; 
 unsigned int EV_KEY ; 
 unsigned int EV_REL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gpio_keys_button_event(struct input_polled_dev *dev,
				   const struct gpio_keys_button *button,
				   int state)
{
	struct gpio_keys_polled_dev *bdev = dev->private;
	struct input_dev *input = dev->input;
	unsigned int type = button->type ?: EV_KEY;

	if (type == EV_REL) {
		if (state) {
			input_event(input, type, button->code, button->value);
			__set_bit(button->code, bdev->rel_axis_seen);
		}
	} else if (type == EV_ABS) {
		if (state) {
			input_event(input, type, button->code, button->value);
			__set_bit(button->code, bdev->abs_axis_seen);
		}
	} else {
		input_event(input, type, button->code, state);
		input_sync(input);
	}
}