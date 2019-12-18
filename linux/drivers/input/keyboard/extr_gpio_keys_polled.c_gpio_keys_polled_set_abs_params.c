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
struct input_dev {int dummy; } ;
struct gpio_keys_platform_data {int nbuttons; struct gpio_keys_button* buttons; } ;
struct gpio_keys_button {scalar_t__ type; unsigned int code; int value; } ;

/* Variables and functions */
 scalar_t__ EV_ABS ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_keys_polled_set_abs_params(struct input_dev *input,
	const struct gpio_keys_platform_data *pdata, unsigned int code)
{
	int i, min = 0, max = 0;

	for (i = 0; i < pdata->nbuttons; i++) {
		const struct gpio_keys_button *button = &pdata->buttons[i];

		if (button->type != EV_ABS || button->code != code)
			continue;

		if (button->value < min)
			min = button->value;
		if (button->value > max)
			max = button->value;
	}

	input_set_abs_params(input, code, min, max, 0, 0);
}