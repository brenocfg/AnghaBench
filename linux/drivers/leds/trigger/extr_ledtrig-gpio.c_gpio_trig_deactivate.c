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
struct led_classdev {int dummy; } ;
struct gpio_trig_data {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct led_classdev*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gpio_trig_data*) ; 
 struct gpio_trig_data* led_get_trigger_data (struct led_classdev*) ; 

__attribute__((used)) static void gpio_trig_deactivate(struct led_classdev *led)
{
	struct gpio_trig_data *gpio_data = led_get_trigger_data(led);

	if (gpio_is_valid(gpio_data->gpio))
		free_irq(gpio_to_irq(gpio_data->gpio), led);
	kfree(gpio_data);
}