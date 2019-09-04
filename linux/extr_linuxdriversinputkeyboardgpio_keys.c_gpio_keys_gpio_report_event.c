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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct gpio_keys_button {int type; int value; int /*<<< orphan*/  code; } ;
struct gpio_button_data {int /*<<< orphan*/ * code; int /*<<< orphan*/  gpiod; struct input_dev* input; struct gpio_keys_button* button; } ;

/* Variables and functions */
 unsigned int EV_ABS ; 
 unsigned int EV_KEY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gpio_keys_gpio_report_event(struct gpio_button_data *bdata)
{
	const struct gpio_keys_button *button = bdata->button;
	struct input_dev *input = bdata->input;
	unsigned int type = button->type ?: EV_KEY;
	int state;

	state = gpiod_get_value_cansleep(bdata->gpiod);
	if (state < 0) {
		dev_err(input->dev.parent,
			"failed to get gpio state: %d\n", state);
		return;
	}

	if (type == EV_ABS) {
		if (state)
			input_event(input, type, button->code, button->value);
	} else {
		input_event(input, type, *bdata->code, state);
	}
	input_sync(input);
}