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
struct ti_ads7950_state {int gpio_cmd_settings_bitmask; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 struct ti_ads7950_state* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int ti_ads7950_get_direction(struct gpio_chip *chip,
				    unsigned int offset)
{
	struct ti_ads7950_state *st = gpiochip_get_data(chip);

	/* Bitmask is inverted from GPIO framework 0=input/1=output */
	return !(st->gpio_cmd_settings_bitmask & BIT(offset));
}