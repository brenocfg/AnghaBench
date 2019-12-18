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
struct sch311x_gpio_block {scalar_t__* config_regs; scalar_t__ runtime_reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct sch311x_gpio_block* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void sch311x_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	struct sch311x_gpio_block *block = gpiochip_get_data(chip);

	if (block->config_regs[offset] == 0) /* GPIO is not available */
		return;

	release_region(block->runtime_reg + block->config_regs[offset], 1);
}