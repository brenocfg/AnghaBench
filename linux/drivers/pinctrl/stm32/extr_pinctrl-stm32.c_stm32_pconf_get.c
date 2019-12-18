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
typedef  int u32 ;
struct stm32_gpio_bank {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ STM32_GPIO_IDR ; 
 scalar_t__ STM32_GPIO_ODR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool stm32_pconf_get(struct stm32_gpio_bank *bank,
	unsigned int offset, bool dir)
{
	unsigned long flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	if (dir)
		val = !!(readl_relaxed(bank->base + STM32_GPIO_IDR) &
			 BIT(offset));
	else
		val = !!(readl_relaxed(bank->base + STM32_GPIO_ODR) &
			 BIT(offset));

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	return val;
}