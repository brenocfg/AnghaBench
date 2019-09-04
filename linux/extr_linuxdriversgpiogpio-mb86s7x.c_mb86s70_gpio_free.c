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
struct mb86s70_gpio_chip {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET (unsigned int) ; 
 scalar_t__ PFR (unsigned int) ; 
 struct mb86s70_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mb86s70_gpio_free(struct gpio_chip *gc, unsigned gpio)
{
	struct mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&gchip->lock, flags);

	val = readl(gchip->base + PFR(gpio));
	val |= OFFSET(gpio);
	writel(val, gchip->base + PFR(gpio));

	spin_unlock_irqrestore(&gchip->lock, flags);
}