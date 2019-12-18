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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_GPIO_DIR1_REG ; 
 int /*<<< orphan*/  ABX500_GPIO_INPUT ; 
 int abx500_gpio_set_bits (struct gpio_chip*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abx500_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	/* set the register as input */
	return abx500_gpio_set_bits(chip,
				AB8500_GPIO_DIR1_REG,
				offset,
				ABX500_GPIO_INPUT);
}