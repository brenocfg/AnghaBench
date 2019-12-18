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
struct thunderx_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct thunderx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ thunderx_gpio_is_gpio (struct thunderx_gpio*,unsigned int) ; 

__attribute__((used)) static int thunderx_gpio_request(struct gpio_chip *chip, unsigned int line)
{
	struct thunderx_gpio *txgpio = gpiochip_get_data(chip);

	return thunderx_gpio_is_gpio(txgpio, line) ? 0 : -EIO;
}