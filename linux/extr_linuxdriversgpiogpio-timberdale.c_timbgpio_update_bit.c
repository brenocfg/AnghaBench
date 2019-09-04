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
typedef  int u32 ;
struct timbgpio {unsigned int membase; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct timbgpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (unsigned int) ; 
 int /*<<< orphan*/  iowrite32 (int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timbgpio_update_bit(struct gpio_chip *gpio, unsigned index,
	unsigned offset, bool enabled)
{
	struct timbgpio *tgpio = gpiochip_get_data(gpio);
	u32 reg;

	spin_lock(&tgpio->lock);
	reg = ioread32(tgpio->membase + offset);

	if (enabled)
		reg |= (1 << index);
	else
		reg &= ~(1 << index);

	iowrite32(reg, tgpio->membase + offset);
	spin_unlock(&tgpio->lock);

	return 0;
}