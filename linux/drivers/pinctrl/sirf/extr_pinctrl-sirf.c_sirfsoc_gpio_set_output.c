#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int regs; } ;
struct sirfsoc_gpio_chip {TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIRFSOC_GPIO_CTL_DATAOUT_MASK ; 
 int /*<<< orphan*/  SIRFSOC_GPIO_CTL_INTR_EN_MASK ; 
 int /*<<< orphan*/  SIRFSOC_GPIO_CTL_OUT_EN_MASK ; 
 int /*<<< orphan*/  readl (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void sirfsoc_gpio_set_output(struct sirfsoc_gpio_chip *sgpio,
					   struct sirfsoc_gpio_bank *bank,
					   unsigned offset,
					   int value)
{
	u32 out_ctrl;
	unsigned long flags;

	spin_lock_irqsave(&bank->lock, flags);

	out_ctrl = readl(sgpio->chip.regs + offset);
	if (value)
		out_ctrl |= SIRFSOC_GPIO_CTL_DATAOUT_MASK;
	else
		out_ctrl &= ~SIRFSOC_GPIO_CTL_DATAOUT_MASK;

	out_ctrl &= ~SIRFSOC_GPIO_CTL_INTR_EN_MASK;
	out_ctrl |= SIRFSOC_GPIO_CTL_OUT_EN_MASK;
	writel(out_ctrl, sgpio->chip.regs + offset);

	spin_unlock_irqrestore(&bank->lock, flags);
}