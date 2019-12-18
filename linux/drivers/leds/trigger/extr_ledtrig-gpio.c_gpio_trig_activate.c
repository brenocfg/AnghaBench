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
struct gpio_trig_data {int /*<<< orphan*/  gpio; struct led_classdev* led; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gpio_trig_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set_trigger_data (struct led_classdev*,struct gpio_trig_data*) ; 

__attribute__((used)) static int gpio_trig_activate(struct led_classdev *led)
{
	struct gpio_trig_data *gpio_data;

	gpio_data = kzalloc(sizeof(*gpio_data), GFP_KERNEL);
	if (!gpio_data)
		return -ENOMEM;

	gpio_data->led = led;
	gpio_data->gpio = -ENOENT;

	led_set_trigger_data(led, gpio_data);

	return 0;
}