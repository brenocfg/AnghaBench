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
struct tqmx86_gpio_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  TQMX86_GPIOD ; 
 struct tqmx86_gpio_data* gpiochip_get_data (struct gpio_chip*) ; 
 int tqmx86_gpio_read (struct tqmx86_gpio_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tqmx86_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct tqmx86_gpio_data *gpio = gpiochip_get_data(chip);

	return !!(tqmx86_gpio_read(gpio, TQMX86_GPIOD) & BIT(offset));
}