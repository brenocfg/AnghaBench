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
struct gpio_fan_data {int num_gpios; int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __set_fan_ctrl(struct gpio_fan_data *fan_data, int ctrl_val)
{
	int i;

	for (i = 0; i < fan_data->num_gpios; i++)
		gpiod_set_value_cansleep(fan_data->gpios[i],
					 (ctrl_val >> i) & 1);
}