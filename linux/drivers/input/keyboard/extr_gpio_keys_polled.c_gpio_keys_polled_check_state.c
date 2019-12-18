#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_polled_dev {TYPE_2__* input; } ;
struct gpio_keys_button_data {int last_state; scalar_t__ count; int /*<<< orphan*/  gpiod; } ;
struct gpio_keys_button {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_keys_button_event (struct input_polled_dev*,struct gpio_keys_button const*,int) ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_keys_polled_check_state(struct input_polled_dev *dev,
					 const struct gpio_keys_button *button,
					 struct gpio_keys_button_data *bdata)
{
	int state;

	state = gpiod_get_value_cansleep(bdata->gpiod);
	if (state < 0) {
		dev_err(dev->input->dev.parent,
			"failed to get gpio state: %d\n", state);
	} else {
		gpio_keys_button_event(dev, button, state);

		if (state != bdata->last_state) {
			bdata->count = 0;
			bdata->last_state = state;
		}
	}
}