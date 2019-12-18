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
struct stm32_gpio_bank {int /*<<< orphan*/  clk; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ STM32_GPIO_BSRR ; 
 scalar_t__ STM32_GPIO_PINS_PER_BANK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_gpio_backup_value (struct stm32_gpio_bank*,unsigned int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void __stm32_gpio_set(struct stm32_gpio_bank *bank,
	unsigned offset, int value)
{
	stm32_gpio_backup_value(bank, offset, value);

	if (!value)
		offset += STM32_GPIO_PINS_PER_BANK;

	clk_enable(bank->clk);

	writel_relaxed(BIT(offset), bank->base + STM32_GPIO_BSRR);

	clk_disable(bank->clk);
}