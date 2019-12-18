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
struct st_gpio_bank {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __st_gpio_set (struct st_gpio_bank*,unsigned int,int) ; 
 struct st_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void st_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct st_gpio_bank *bank = gpiochip_get_data(chip);
	__st_gpio_set(bank, offset, value);
}