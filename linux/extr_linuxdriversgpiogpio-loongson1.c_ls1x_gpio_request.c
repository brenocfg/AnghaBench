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
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ GPIO_CFG ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ gpio_reg_base ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ls1x_gpio_request(struct gpio_chip *gc, unsigned int offset)
{
	unsigned long flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	__raw_writel(__raw_readl(gpio_reg_base + GPIO_CFG) | BIT(offset),
		     gpio_reg_base + GPIO_CFG);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	return 0;
}