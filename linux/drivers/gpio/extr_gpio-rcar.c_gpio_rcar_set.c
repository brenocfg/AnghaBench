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
struct gpio_rcar_priv {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTDT ; 
 int /*<<< orphan*/  gpio_rcar_modify_bit (struct gpio_rcar_priv*,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpio_rcar_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct gpio_rcar_priv *p = gpiochip_get_data(chip);
	unsigned long flags;

	spin_lock_irqsave(&p->lock, flags);
	gpio_rcar_modify_bit(p, OUTDT, offset, value);
	spin_unlock_irqrestore(&p->lock, flags);
}