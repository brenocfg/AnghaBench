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
typedef  unsigned int u32 ;

/* Variables and functions */
 int LPC18XX_GPIO_PINS_PER_PORT ; 
 unsigned int LPC18XX_SCU_PINTSEL_PORT_SHIFT ; 

__attribute__((used)) static u32 lpc18xx_gpio_to_pintsel_val(int gpio)
{
	unsigned int gpio_port, gpio_pin;

	gpio_port = gpio / LPC18XX_GPIO_PINS_PER_PORT;
	gpio_pin  = gpio % LPC18XX_GPIO_PINS_PER_PORT;

	return gpio_pin | (gpio_port << LPC18XX_SCU_PINTSEL_PORT_SHIFT);
}