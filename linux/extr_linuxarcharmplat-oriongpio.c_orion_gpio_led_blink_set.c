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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
#define  GPIO_LED_BLINK 130 
#define  GPIO_LED_NO_BLINK_HIGH 129 
#define  GPIO_LED_NO_BLINK_LOW 128 
 unsigned long ORION_BLINK_HALF_PERIOD ; 
 unsigned int desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  orion_gpio_set_blink (unsigned int,int) ; 

int orion_gpio_led_blink_set(struct gpio_desc *desc, int state,
	unsigned long *delay_on, unsigned long *delay_off)
{
	unsigned gpio = desc_to_gpio(desc);

	if (delay_on && delay_off && !*delay_on && !*delay_off)
		*delay_on = *delay_off = ORION_BLINK_HALF_PERIOD;

	switch (state) {
	case GPIO_LED_NO_BLINK_LOW:
	case GPIO_LED_NO_BLINK_HIGH:
		orion_gpio_set_blink(gpio, 0);
		gpio_set_value(gpio, state);
		break;
	case GPIO_LED_BLINK:
		orion_gpio_set_blink(gpio, 1);
	}
	return 0;
}