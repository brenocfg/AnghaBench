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
struct gpio_bank {int /*<<< orphan*/  irq_usage; int /*<<< orphan*/  mod_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  LINE_USED (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  omap_enable_gpio_module (struct gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  omap_set_gpio_direction (struct gpio_bank*,unsigned int,int) ; 

__attribute__((used)) static void omap_gpio_init_irq(struct gpio_bank *bank, unsigned offset)
{
	if (!LINE_USED(bank->mod_usage, offset)) {
		omap_enable_gpio_module(bank, offset);
		omap_set_gpio_direction(bank, offset, 1);
	}
	bank->irq_usage |= BIT(offset);
}