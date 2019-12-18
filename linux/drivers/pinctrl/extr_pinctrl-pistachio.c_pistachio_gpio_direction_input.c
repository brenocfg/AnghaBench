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
struct pistachio_gpio_bank {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUTPUT_EN ; 
 int /*<<< orphan*/  gpio_enable (struct pistachio_gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  gpio_mask_writel (struct pistachio_gpio_bank*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct pistachio_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int pistachio_gpio_direction_input(struct gpio_chip *chip,
					  unsigned offset)
{
	struct pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	gpio_mask_writel(bank, GPIO_OUTPUT_EN, offset, 0);
	gpio_enable(bank, offset);

	return 0;
}