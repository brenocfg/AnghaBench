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
struct gpio_chip {scalar_t__ base; int /*<<< orphan*/  label; } ;
struct egpio_info {int reg_shift; int reg_mask; int /*<<< orphan*/  lock; } ;
struct egpio_chip {int reg_start; int cached_values; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct egpio_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int egpio_pos (struct egpio_info*,unsigned int) ; 
 int /*<<< orphan*/  egpio_writew (int,struct egpio_info*,int) ; 
 struct egpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void egpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned long     flag;
	struct egpio_chip *egpio;
	struct egpio_info *ei;
	int               pos;
	int               reg;
	int               shift;

	pr_debug("egpio_set(%s, %d(%d), %d)\n",
			chip->label, offset, offset+chip->base, value);

	egpio = gpiochip_get_data(chip);
	ei    = dev_get_drvdata(egpio->dev);
	pos   = egpio_pos(ei, offset);
	reg   = egpio->reg_start + pos;
	shift = pos << ei->reg_shift;

	pr_debug("egpio %s: reg %d = 0x%04x\n", value ? "set" : "clear",
			reg, (egpio->cached_values >> shift) & ei->reg_mask);

	spin_lock_irqsave(&ei->lock, flag);
	if (value)
		egpio->cached_values |= (1 << offset);
	else
		egpio->cached_values &= ~(1 << offset);
	egpio_writew((egpio->cached_values >> shift) & ei->reg_mask, ei, reg);
	spin_unlock_irqrestore(&ei->lock, flag);
}