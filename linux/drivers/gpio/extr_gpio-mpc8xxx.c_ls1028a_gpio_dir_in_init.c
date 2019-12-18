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
struct mpc8xxx_gpio_chip {scalar_t__ regs; } ;
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  (* write_reg ) (scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ GPIO_IBE ; 
 struct mpc8xxx_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 

__attribute__((used)) static int ls1028a_gpio_dir_in_init(struct gpio_chip *gc)
{
	unsigned long flags;
	struct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	gc->write_reg(mpc8xxx_gc->regs + GPIO_IBE, 0xffffffff);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	return 0;
}