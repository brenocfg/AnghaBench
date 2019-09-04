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
struct xgene_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xgene_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct xgene_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xgene_gpio_set(struct gpio_chip *gc, unsigned int offset, int val)
{
	struct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);
	__xgene_gpio_set(gc, offset, val);
	spin_unlock_irqrestore(&chip->lock, flags);
}