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
struct gpio_reg {unsigned long out; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gpio_reg* to_gpio_reg (struct gpio_chip*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_reg_set_multiple(struct gpio_chip *gc, unsigned long *mask,
	unsigned long *bits)
{
	struct gpio_reg *r = to_gpio_reg(gc);
	unsigned long flags;

	spin_lock_irqsave(&r->lock, flags);
	r->out = (r->out & ~*mask) | (*bits & *mask);
	writel_relaxed(r->out, r->reg);
	spin_unlock_irqrestore(&r->lock, flags);
}