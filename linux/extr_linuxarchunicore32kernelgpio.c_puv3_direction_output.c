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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GPDR ; 
 int GPIO_GPIO (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  puv3_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_direction_output(struct gpio_chip *chip, unsigned offset,
		int value)
{
	unsigned long flags;

	local_irq_save(flags);
	puv3_gpio_set(chip, offset, value);
	writel(readl(GPIO_GPDR) | GPIO_GPIO(offset), GPIO_GPDR);
	local_irq_restore(flags);
	return 0;
}