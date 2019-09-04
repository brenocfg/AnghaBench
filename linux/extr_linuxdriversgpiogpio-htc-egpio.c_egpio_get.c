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
struct gpio_chip {scalar_t__ base; } ;
struct egpio_info {int bus_shift; int /*<<< orphan*/  base_addr; } ;
struct egpio_chip {int reg_start; int cached_values; int /*<<< orphan*/  is_out; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct egpio_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned int egpio_bit (struct egpio_info*,unsigned int) ; 
 int egpio_pos (struct egpio_info*,unsigned int) ; 
 int egpio_readw (struct egpio_info*,int) ; 
 struct egpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int egpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct egpio_chip *egpio;
	struct egpio_info *ei;
	unsigned           bit;
	int                reg;
	int                value;

	pr_debug("egpio_get_value(%d)\n", chip->base + offset);

	egpio = gpiochip_get_data(chip);
	ei    = dev_get_drvdata(egpio->dev);
	bit   = egpio_bit(ei, offset);
	reg   = egpio->reg_start + egpio_pos(ei, offset);

	if (test_bit(offset, &egpio->is_out)) {
		return !!(egpio->cached_values & (1 << offset));
	} else {
		value = egpio_readw(ei, reg);
		pr_debug("readw(%p + %x) = %x\n",
			 ei->base_addr, reg << ei->bus_shift, value);
		return !!(value & bit);
	}
}