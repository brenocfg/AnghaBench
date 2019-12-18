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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ regs; } ;
struct sirfsoc_gpio_chip {int /*<<< orphan*/  lock; TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ SIRFSOC_GPIO_CTL_INTR_EN_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTL_INTR_STS_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,int) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void __sirfsoc_gpio_irq_mask(struct sirfsoc_gpio_chip *sgpio,
				    struct sirfsoc_gpio_bank *bank,
				    int idx)
{
	u32 val, offset;
	unsigned long flags;

	offset = SIRFSOC_GPIO_CTRL(bank->id, idx);

	spin_lock_irqsave(&sgpio->lock, flags);

	val = readl(sgpio->chip.regs + offset);
	val &= ~SIRFSOC_GPIO_CTL_INTR_EN_MASK;
	val &= ~SIRFSOC_GPIO_CTL_INTR_STS_MASK;
	writel(val, sgpio->chip.regs + offset);

	spin_unlock_irqrestore(&sgpio->lock, flags);
}