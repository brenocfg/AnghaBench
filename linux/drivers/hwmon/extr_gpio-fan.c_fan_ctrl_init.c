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
struct gpio_fan_data {int num_gpios; int pwm_enable; scalar_t__ speed_index; struct gpio_desc** gpios; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_fan_speed_index (struct gpio_fan_data*) ; 
 int gpiod_direction_output (struct gpio_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (struct gpio_desc*) ; 

__attribute__((used)) static int fan_ctrl_init(struct gpio_fan_data *fan_data)
{
	int num_gpios = fan_data->num_gpios;
	struct gpio_desc **gpios = fan_data->gpios;
	int i, err;

	for (i = 0; i < num_gpios; i++) {
		/*
		 * The GPIO descriptors were retrieved with GPIOD_ASIS so here
		 * we set the GPIO into output mode, carefully preserving the
		 * current value by setting it to whatever it is already set
		 * (no surprise changes in default fan speed).
		 */
		err = gpiod_direction_output(gpios[i],
					gpiod_get_value_cansleep(gpios[i]));
		if (err)
			return err;
	}

	fan_data->pwm_enable = true; /* Enable manual fan speed control. */
	fan_data->speed_index = get_fan_speed_index(fan_data);
	if (fan_data->speed_index < 0)
		return fan_data->speed_index;

	return 0;
}