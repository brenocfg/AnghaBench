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
typedef  int /*<<< orphan*/  u8 ;
struct sch311x_gpio_block {int /*<<< orphan*/  lock; scalar_t__* config_regs; scalar_t__ runtime_reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCH311X_GPIO_CONF_DIR ; 
 int /*<<< orphan*/  __sch311x_gpio_set (struct sch311x_gpio_block*,unsigned int,int) ; 
 struct sch311x_gpio_block* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sch311x_gpio_direction_out(struct gpio_chip *chip, unsigned offset,
				      int value)
{
	struct sch311x_gpio_block *block = gpiochip_get_data(chip);
	u8 data;

	spin_lock(&block->lock);

	data = inb(block->runtime_reg + block->config_regs[offset]);
	data &= ~SCH311X_GPIO_CONF_DIR;
	outb(data, block->runtime_reg + block->config_regs[offset]);
	__sch311x_gpio_set(block, offset, value);

	spin_unlock(&block->lock);
	return 0;
}