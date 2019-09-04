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
typedef  int u32 ;
struct pch_gpio {int /*<<< orphan*/  spinlock; TYPE_1__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  po; } ;

/* Variables and functions */
 struct pch_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pch_gpio_set(struct gpio_chip *gpio, unsigned nr, int val)
{
	u32 reg_val;
	struct pch_gpio *chip =	gpiochip_get_data(gpio);
	unsigned long flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	reg_val = ioread32(&chip->reg->po);
	if (val)
		reg_val |= (1 << nr);
	else
		reg_val &= ~(1 << nr);

	iowrite32(reg_val, &chip->reg->po);
	spin_unlock_irqrestore(&chip->spinlock, flags);
}