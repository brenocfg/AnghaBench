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
struct gpio {int output_state; } ;
typedef  enum gpio_pin_output_state { ____Placeholder_gpio_pin_output_state } gpio_pin_output_state ;

/* Variables and functions */

enum gpio_pin_output_state dal_gpio_get_output_state(
	const struct gpio *gpio)
{
	return gpio->output_state;
}