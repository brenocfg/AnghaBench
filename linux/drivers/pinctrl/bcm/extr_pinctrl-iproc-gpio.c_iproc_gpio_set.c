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
struct iproc_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_GPIO_DATA_OUT_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 struct iproc_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  iproc_set_bit (struct iproc_gpio*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iproc_gpio_set(struct gpio_chip *gc, unsigned gpio, int val)
{
	struct iproc_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_DATA_OUT_OFFSET, gpio, !!(val));
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set, value:%d\n", gpio, val);
}