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
typedef  int /*<<< orphan*/  u32 ;
struct gpio_reg {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  out; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gpio_reg* to_gpio_reg (struct gpio_chip*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_reg_set(struct gpio_chip *gc, unsigned offset, int value)
{
	struct gpio_reg *r = to_gpio_reg(gc);
	unsigned long flags;
	u32 val, mask = BIT(offset);

	spin_lock_irqsave(&r->lock, flags);
	val = r->out;
	if (value)
		val |= mask;
	else
		val &= ~mask;
	r->out = val;
	writel_relaxed(val, r->reg);
	spin_unlock_irqrestore(&r->lock, flags);
}