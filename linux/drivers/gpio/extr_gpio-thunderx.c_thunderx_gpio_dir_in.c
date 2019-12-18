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
struct thunderx_gpio {int /*<<< orphan*/  lock; scalar_t__ register_base; TYPE_1__* line_entries; int /*<<< orphan*/  od_mask; int /*<<< orphan*/  invert_mask; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fil_bits; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ bit_cfg_reg (unsigned int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct thunderx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thunderx_gpio_is_gpio (struct thunderx_gpio*,unsigned int) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int thunderx_gpio_dir_in(struct gpio_chip *chip, unsigned int line)
{
	struct thunderx_gpio *txgpio = gpiochip_get_data(chip);

	if (!thunderx_gpio_is_gpio(txgpio, line))
		return -EIO;

	raw_spin_lock(&txgpio->lock);
	clear_bit(line, txgpio->invert_mask);
	clear_bit(line, txgpio->od_mask);
	writeq(txgpio->line_entries[line].fil_bits,
	       txgpio->register_base + bit_cfg_reg(line));
	raw_spin_unlock(&txgpio->lock);
	return 0;
}